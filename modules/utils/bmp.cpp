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
		db_dbg_msg( "file_header.type = " + std::to_string( _file_header.type ) + "\n" );
		db_dbg_msg( "file_header.size = " + std::to_string( _file_header.size ) + " bytes\n" );

		// Проверка типа файла
		if ( _file_header.type != 0x4D42 ) {
			db_dbg_error( "file header -> wrong type. big endian?\n" );
			return 0;
		}

		// Чтение заголовка информации о файле

		// Чтение значений для версии CORE
		file->read( ( char* )&_info_header, BMP_COLOR_HEADER_SIZE_CORE + 4 );	// Поле size не учитывается в размере, поэтому +4 байта
		db_dbg_msg( "info_header.header size = " + std::to_string( _info_header.size ) + " bytes\n" );
		db_dbg_msg( "info_header.width = " + std::to_string( _info_header.width ) + "\n" );
		db_dbg_msg( "info_header.height = " + std::to_string( _info_header.height ) + "\n" );
		db_dbg_msg( "info_header.bpp = " + std::to_string( _info_header.bpp ) + "\n" );

		// Получение версии bmp
		bmp_info_header_s::version_s version = _info_header.get_version( );
		switch( version ) {
			case bmp_info_header_s::VERSION_CORE: {
				db_dbg_msg( "info_header.version = CORE\n" );
				break;
			}

			case bmp_info_header_s::VERSION_3: {
				db_dbg_msg( "info_header.version = 3\n" );

				// Считываю оставшиеся байты структуры bmp_info_header
				file->read( ( char* )&_info_header + BMP_COLOR_HEADER_SIZE_CORE + 4,
				            BMP_COLOR_HEADER_SIZE_V3 - BMP_COLOR_HEADER_SIZE_CORE + 4 );
				break;
			}

			case bmp_info_header_s::VERSION_4: {
				db_dbg_msg( "info_header.version = 4\n" );

				// Считываю оставшиеся байты структуры bmp_info_header
				file->read( ( char* )&_info_header + BMP_COLOR_HEADER_SIZE_CORE + 4,
				            BMP_COLOR_HEADER_SIZE_V3 - BMP_COLOR_HEADER_SIZE_CORE + 4 );	// V3 - корректно

				db_dbg_msg( "info_header.compression = " + std::to_string( _info_header.compression ) + "\n" );
				db_dbg_msg( "info_header.palette color used = " + std::to_string( _info_header.used_color_ind ) + "\n" );
				db_dbg_msg( "info_header.colors = " + std::to_string( _info_header.color_req ) + "\n" );

				// Проверка поддержки типа сжатия изображения
				bmp_info_header_s::compression_s comp = _info_header.get_compression( );
				if ( !( comp == bmp_info_header_s::CMP_BI_RGB ) || !( comp == bmp_info_header_s::CMP_BI_BITFIELDS ) ) {
					db_dbg_error( "info header -> unsupported compression format\n" );
					return 0;
				}

				// Считываю bmp_color_header_s
				file->read( ( char* )&_color_header, sizeof( bmp_color_header_s ) );
				db_dbg_msg( "color_header.red_mask =  " + std::to_string( _color_header.red_mask ) );
				db_dbg_msg( "color_header.green_mask =  " + std::to_string( _color_header.green_mask ) );
				db_dbg_msg( "color_header.blue_mask =  " + std::to_string( _color_header.blue_mask ) );
				db_dbg_msg( "color_header.alpha_mask =  " + std::to_string( _color_header.alpha_mask ) );

				// Проверка поддержки маски цвета BGRA и цветового пространства sRGB
				if ( !_color_header.is_bgra( ) || !_color_header.is_srgb( ) ) {
					db_dbg_error( "color header -> unsupported color format\n" );
					return 0;
				}

				break;
			}

			case bmp_info_header_s::VERSION_5: {
				db_dbg_msg( "info_header.version = 5\n" );
				db_dbg_error("version 5 BMP files are not supported. Contact the developer");
				return 0;
			}
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
			db_dbg_error( "unsupported bpp\n" );
			return 0;
		}

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
				db_dbg_warn( "wrong file header size, corrected ( 32bpp )\n" );
				_file_header.offset_data = size_headers;
			}

			// Корректировка структуры информации файла
			if ( _info_header.size != size_info_color ) {
				db_dbg_warn( "wrong info header size, corrected ( 32bpp )\n" );
				_info_header.size = size_info_color;
			}
			// Иначе, если в файле нет альфа - канала
		} else {
			size_info = sizeof( bmp_info_header_s );
			size_headers = sizeof( bmp_file_header_s ) + sizeof( bmp_info_header_s );

			// Корректировка  структуры заголовка
			if ( _file_header.offset_data != size_headers ) {
				db_dbg_warn( "wrong file header size, corrected ( 24bpp )\n" );
				_file_header.offset_data = size_headers;
			}

			// Корректировка структуры информации файла
			if ( _info_header.size != size_info ) {
				db_dbg_warn( "wrong info header size, corrected ( 24bpp )\n" );
				_info_header.size = size_info;
			}
		}	// if transparent

		_file_header.size = _file_header.offset_data;

		// Проверка соответствия формата файла: начало должно быть с верхнего левого угла
		if ( _info_header.height < 0 ) {
			db_dbg_error( "info header: bottom - left origin unsupported\n" );
			return 0;
		}

		// Выделение памяти под массив пикселей
		_data.resize( _info_header.width * _info_header.height * _info_header.bpp / 8 );

		// Количество байт в строке должно быть кратным 4
		// Проверка, нужно ли выравнивание строк
		if ( _info_header.width % 4 == 0 ) {
			// Выравнивание не нужно, просто считывается массив пикселей
			file->read( ( char* )_data.data( ), _data.size( ) );
			_file_header.size += static_cast< uint8_t >( _data.size( ) );

		} else {
			// Выравнивание нужно
			db_dbg_warn( "incorrect row padding. Try to align...\n" );

			// Расчет размера отступа после каждой строки в байтах
			uint32_t padding = ( ( 4 - ( _info_header.width * _info_header.bpp / 8 ) ) % 4 ) & 3;

			for ( int32_t i = 0; i < _info_header.height; i++ ) {
				for ( int32_t i = 0; i < _info_header.width; i++ )
					file->read( ( char* )( _data.data( ) ), _info_header.height );
				file->seekg( padding, std::ios_base::cur );
			}

			/*

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
			#ifdef DB_DEBUG
			debug::get_instance( )->message( std::string( __FUNCTION__ ) + " -> alignment done\n" );
			#endif // DB_DEBUG
			*/
			db_dbg_warn( "alignment done\n" );

		}

		// Successfull
		return 1;
	}

	bool bmp::load_from_file( std::string file_name ) {

		// Открытие файла
		std::ifstream file;
		file.open( file_name, std::ios_base::binary );
		if ( !file.is_open( ) ) {
			db_dbg_error( "cannot open file\n" );
			return 0;
		}

		// Чтение заголовков
		if ( !_read_header( &file ) ) {
			db_dbg_error( "error while reading headers\n" );
			file.close( );
			return 0;
		}

		// Переход к массиву пикселей
		file.seekg( _file_header.offset_data, file.beg );

		// Чтение заголовков
		if ( !_read_pixel_data( &file ) ) {
			db_dbg_error( "error while reading pixel data\n" );
			file.close( );
			return 0;
		}

		// Конвертация BGR -> RGB / BGRA -> RGBA
		if ( !convert_format( ) )
			db_dbg_warn( "cannot convert to RGB(A)\n" );

		// Success
		return 1;
	}

	bool bmp::save_to_file( std::string file_name ) {
		db_dbg_msg( "currently unsupported\n" );
		return 0;
	}

	// ==== bmp_info_header_s ====
	bmp::bmp_info_header_s::version_s bmp::bmp_info_header_s::get_version( void ) {
		version_s ver;
		switch ( size ) {
			case BMP_COLOR_HEADER_SIZE_CORE: {
				ver = VERSION_CORE;
				break;
			}
			case BMP_COLOR_HEADER_SIZE_V3: {
				ver = VERSION_3;
				break;
			}
			case BMP_COLOR_HEADER_SIZE_V4: {
				ver = VERSION_4;
				break;
			}
			case BMP_COLOR_HEADER_SIZE_V5: {
				ver = VERSION_5;
				break;
			}
			default: {
				db_dbg_error( "wrong _size_ field. Cannot get version of bmp image" );
				ver = VERSION_CORE;
			}
		}
		return ver;
	}

	bmp::bmp_info_header_s::compression_s bmp::bmp_info_header_s::get_compression( void ) {
		return ( compression_s )compression;
	}

	// ==== bmp_info_header_s ====


	// ==== bmp_color_header_s ====

	bool  bmp::bmp_color_header_s::is_bgr( void ) {
		return (	red_mask			== 0x00ff0000 &&
		            green_mask			== 0x0000ff00 &&
		            blue_mask			== 0x000000ff &&
		            alpha_mask			== 0x00000000 );
	}

	bool  bmp::bmp_color_header_s::is_bgra( void ) {
		return (	red_mask			== 0x00ff0000 &&
		            green_mask			== 0x0000ff00 &&
		            blue_mask			== 0x000000ff &&
		            alpha_mask			== 0xff000000 );
	}

	bool  bmp::bmp_color_header_s::is_rgb( void ) {
		return (	red_mask			== 0x000000ff &&
		            green_mask			== 0x0000ff00 &&
		            blue_mask			== 0x00ff0000 &&
		            alpha_mask			== 0x00000000 );
	}

	bool  bmp::bmp_color_header_s::is_rgba( void ) {
		return (	red_mask			== 0x000000ff &&
		            green_mask			== 0x0000ff00 &&
		            blue_mask			== 0x00ff0000 &&
		            alpha_mask			== 0xff000000 );
	}

	bool  bmp::bmp_color_header_s::is_srgb( void ) {
		return ( color_space_type	== 0x73524742 );
	}

	// ==== bmp_color_header_s ====

}	// namespace demonblade

