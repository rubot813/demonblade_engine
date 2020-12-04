#include "bmp.hpp"

namespace demonblade {

	bmp::bmp( void ) {
		#ifdef __linux
		_data.clear( );
		#endif	// ifdef __linux
	}
	bmp::bmp( std::string file_name ) {
		load_from_file( file_name );
	}

	bmp::~bmp( void ) {
		// nope
	}

	bool bmp::_read_header( std::ifstream *file ) {

		// Чтение заголовка файла
		file->read( ( char* )&_file_header, sizeof( bmp_file_header_s ) );

		// Проверка типа файла
		if ( _file_header.file_type != 0x4D42 ) {
			#ifdef DB_DEBUG
			debug::get_instance( )->error( std::string( __FUNCTION__ ) + " -> file header -> wrong type\n" );
			#endif // DB_DEBUG
			return 0;
		}

		// Чтение заголовка информации о файле
		file->read( ( char* )&_info_header, sizeof( bmp_info_header_s ) );

		// Если в файле есть альфа - канал, чтение заголовка bmp_color_header
		if ( _info_header.bpp == 32 ) {

			// Проверка, имеет ли файл информацию о маске цвета
			if ( _info_header.size >= ( sizeof( bmp_info_header_s ) + sizeof( bmp_color_header_s ) ) ) {	// Ну я хуй знает здесь, какая то ебола, но допустим

				// Чтение заголовка color_header
				file->read( ( char* )&_color_header, sizeof( bmp_color_header_s ) );

				// Проверка поддержки маски цвета
				if ( !_color_header.is_valid_format( ) ) {
					#ifdef DB_DEBUG
					debug::get_instance( )->error( std::string( __FUNCTION__ ) + " -> color header -> unsupported color format\n" );
					#endif // DB_DEBUG
					return 0;
				}
			} else {
				#ifdef DB_DEBUG
				debug::get_instance( )->error( std::string( __FUNCTION__ ) + " -> color header -> file not contain color mask info\n" );
				#endif // DB_DEBUG

				return 0;
			}

		}	// if transparent

		return 1;
	}

	bool bmp::_read_pixel_data( std::ifstream *file ) {

		// Здесь происходит корректировка заголовков
		// Некоторые редакторы помещают дополнительную информацию
		uint32_t size_info_color;
		uint32_t size_info;
		uint32_t size_headers;

		// Если в файле есть альфа - канал
		if ( _info_header.bpp == 32 ) {
			size_info_color = sizeof( bmp_info_header_s ) + sizeof( bmp_color_header_s );
			size_headers = sizeof( bmp_file_header_s ) + sizeof( bmp_info_header_s ) + sizeof( bmp_color_header_s );

			// Корректировка структуры заголовка
			if ( _file_header.offset_data != size_headers ) {
				#ifdef DB_DEBUG
				debug::get_instance( )->warn( std::string( __FUNCTION__ ) + " -> wrong file header size, corrected ( 32bpp )\n" );
				#endif // DB_DEBUG
				_file_header.offset_data = size_headers;
			}

			// Корректировка структуры информации файла
			if ( _info_header.size != size_info_color ) {
				#ifdef DB_DEBUG
				debug::get_instance( )->warn( std::string( __FUNCTION__ ) + " -> wrong info header size, corrected ( 32bpp )\n" );
				#endif // DB_DEBUG
				_info_header.size = size_info_color;
			}
			// Иначе, если в файле нет альфа - канала
		} else {
			size_info = sizeof( bmp_info_header_s );
			size_headers = sizeof( bmp_file_header_s ) + sizeof( bmp_info_header_s );

			// Корректировка  структуры заголовка
			if ( _file_header.offset_data != size_headers ) {
				#ifdef DB_DEBUG
				debug::get_instance( )->warn( std::string( __FUNCTION__ ) + " -> wrong file header size, corrected ( 24bpp )\n" );
				#endif // DB_DEBUG
				_file_header.offset_data = size_headers;
			}

			// Корректировка структуры информации файла
			if ( _info_header.size != size_info ) {
				#ifdef DB_DEBUG
				debug::get_instance( )->warn( std::string( __FUNCTION__ ) + " -> wrong info header size, corrected ( 24bpp )\n" );
				#endif // DB_DEBUG
				_info_header.size = size_info;
			}
		}	// if transparent

		_file_header.file_size = _file_header.offset_data;

		// Проверка соответствия формата файла: начало должно быть с верхнего левого угла
		if ( _info_header.height < 0 ) {
			#ifdef DB_DEBUG
			debug::get_instance( )->error( std::string( __FUNCTION__ ) + " -> info header: bottom - left origin unsupported\n" );
			#endif // DB_DEBUG
			return 0;
		}

		// Выделение памяти под массив пикселей
		_data.resize( _info_header.width * _info_header.height * _info_header.bpp / 8 );

		// Проверка, нужно ли выравнивание строк
		if ( _info_header.width % 4 == 0 ) {
			// Выравнивание не нужно
			file->read( ( char* )_data.data( ), _data.size( ) );
			_file_header.file_size += static_cast< uint8_t >( _data.size( ) );

		} else {
			// Выравнивание нужно
			uint32_t row_stride = _info_header.width * _info_header.bpp / 8;
			uint32_t stride = row_stride;
			while ( stride % 4 != 0 )
				stride++;
			std::vector< uint8_t > padding_row( stride - row_stride );
			for ( int32_t i = 0; i < _info_header.height; i++ ) {
				file->read( ( char* )( _data.data( ) + row_stride * i ), row_stride );
				file->read( ( char* )padding_row.data( ), padding_row.size( ) );
			}
			_file_header.file_size += static_cast< uint32_t >( _data.size( ) ) + _info_header.height * static_cast< uint32_t >( padding_row.size( ) );
		}

		// Successfull
		return 1;
	}

	bool bmp::load_from_file( std::string file_name ) {

		// Открытие файла
		std::ifstream file;
		file.open( file_name, std::ios_base::binary );
		if ( !file.is_open( ) ) {
			#ifdef DB_DEBUG
			debug::get_instance( )->error( std::string( __FUNCTION__ ) + " -> cannot open file\n" );
			#endif // DB_DEBUG
			return 0;
		}

		// Чтение заголовков
		if ( !_read_header( &file ) ) {
			#ifdef DB_DEBUG
			debug::get_instance( )->error( std::string( __FUNCTION__ ) + " -> cannot parse headers\n" );
			#endif // DB_DEBUG
			file.close( );
			return 0;
		}

		// Переход к массиву пикселей
		file.seekg( _file_header.offset_data, file.beg );

		// Чтение заголовков
		if ( !_read_pixel_data( &file ) ) {
			#ifdef DB_DEBUG
			debug::get_instance( )->error( std::string( __FUNCTION__ ) + " -> cannot read pixel array\n" );
			#endif // DB_DEBUG
			file.close( );
			return 0;
		}

		// Установка размеров изображения
		_width	= _info_header.width;
		_height = _info_header.height;

		// Установка расширенного формата файла
		if ( _info_header.bpp == 24 )
			_format = SIZED_RGB;
		else if ( _info_header.bpp == 32 )
			_format = SIZED_RGBA;
		else {
			#ifdef DB_DEBUG
			debug::get_instance( )->error( std::string( __FUNCTION__ ) + " -> cannot read bpp field\n" );
			#endif // DB_DEBUG
		}

		// Конвертация BGR -> RGB / BGRA -> RGBA
		if ( !convert_format( ) ) {
			#ifdef DB_DEBUG
			debug::get_instance( )->error( std::string( __FUNCTION__ ) + " -> cannot convert to RGB(A)\n" );
			#endif // DB_DEBUG
		}

		// Success
		return 1;
	}

	bool bmp::save_to_file( std::string file_name ) {
		#ifdef DB_DEBUG
		debug::get_instance( )->message( std::string( __FUNCTION__ ) + " -> currently unsupported\n" );
		#endif // DB_DEBUG
		return 0;
	}

	bool bmp::bmp_color_header_s::is_valid_format( void ) {
		// mask = BGRA, space = sRGB
		return (	red_mask			== 0x00ff0000 &&
		            green_mask			== 0x0000ff00 &&
		            blue_mask			== 0x000000ff &&
		            alpha_mask			== 0xff000000 &&
		            color_space_type	== 0x73524742 );
	}

}	// namespace demonblade

