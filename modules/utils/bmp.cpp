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

	// ����� �������� ����������� �� �����
	bool bmp::load_from_file( std::string file_name ) {
		/*
		// �������� �����
		std::ifstream file;
		file.open( file_name, std::ios_base::binary );
		if ( !file.is_open( ) ) {
			#ifdef DB_DEBUG
			debug::get_instance( )->error( std::string( __FUNCTION__ ) + " -> cannot open file\n" );
			#endif // DB_DEBUG
			return 0;
		}

		// ������ ��������� bmp_header
		file.read( ( char* )&_header, sizeof( bmp_header_s ) );
		if ( _header.file_type != 0x4D42 ) {
			#ifdef DB_DEBUG
			debug::get_instance( )->error( std::string( __FUNCTION__ ) + " -> header -> wrong file type\n" );
			#endif // DB_DEBUG
			file.close( );
			return 0;
		}

		// ������ ��������� bmp_info_header
		file.read( ( char* )&_info_header, sizeof( bmp_info_header_s ) );

		// ���� ����������, ������� �� ����� - ����� � �����������
		bool transparent = ( _info_header.bpp == 32 );

		// ������ ��������� bmp_color_header ( ������ ��� ������� ������������ )
		if ( transparent ) {
			// ��������, ����� �� ���� ���������� � ����� �����
			if ( _info_header.size >= ( sizeof( bmp_info_header_s ) + sizeof( bmp_color_header_s ) ) ) {
				// ������ ��������� bmp_color_header
				file.read( ( char* )&_color_header, sizeof( bmp_color_header_s ) );

				// �������� ��������� ����� �����
				if ( !_color_header.is_correct_type( ) ) {
					#ifdef DB_DEBUG
					debug::get_instance( )->error( std::string( __FUNCTION__ ) + " -> color header -> unsupported color format\n" );
					#endif // DB_DEBUG
					file.close( );
					return 0;
				}

			} else {
				#ifdef DB_DEBUG
				debug::get_instance( )->error( std::string( __FUNCTION__ ) + " -> color header -> file not contain color mask info\n" );
				#endif // DB_DEBUG
				file.close( );
				return 0;
			}

		}	// if transparent

		// ������� � ������� ��������
		file.seekg( _header.offset_data, file.beg );

		// ����� ���������� ������������� ����������
		// ��������� ��������� �������� �������������� ����������
		uint32_t size_info_color;
		uint32_t size_info;
		uint32_t size_headers;

		if ( transparent ) {
			// 32 ��� / �������
			size_info_color = sizeof( bmp_info_header_s ) + sizeof( bmp_color_header_s );
			size_headers = sizeof( bmp_header_s ) + sizeof( bmp_info_header_s ) + sizeof( bmp_color_header_s );

			// ������������� ��������� ���������
			if ( _header.offset_data != size_headers ) {
				#ifdef DB_DEBUG
				debug::get_instance( )->warn( std::string( __FUNCTION__ ) + " -> wrong header size, corrected ( 32bpp )\n" );
				#endif // DB_DEBUG
				_header.offset_data = size_headers;
			}

			// ������������� ��������� ���������� �����
			if ( _info_header.size != size_info_color ) {
				#ifdef DB_DEBUG
				debug::get_instance( )->warn( std::string( __FUNCTION__ ) + " -> wrong info header size, corrected ( 32bpp )\n" );
				#endif // DB_DEBUG
				_info_header.size = size_info_color;
			}
		} else {
			// 24 ��� / �������
			size_info = sizeof( bmp_info_header_s );
			size_headers = sizeof( bmp_header_s ) + sizeof( bmp_info_header_s );

			// �������������  ��������� ���������
			if ( _header.offset_data != size_headers ) {
				#ifdef DB_DEBUG
				debug::get_instance( )->warn( std::string( __FUNCTION__ ) + " -> wrong header size, corrected ( 24bpp )\n" );
				#endif // DB_DEBUG
				_header.offset_data = size_headers;
			}

			// ������������� ��������� ���������� �����
			if ( _info_header.size != size_info ) {
				#ifdef DB_DEBUG
				debug::get_instance( )->warn( std::string( __FUNCTION__ ) + " -> wrong info header size, corrected ( 24bpp )\n" );
				#endif // DB_DEBUG
				_info_header.size = size_info;
			}
		}	// if transparent

		_header.file_size = _header.offset_data;

		// �������� ������������ ������� �����: ������ ������ ���� � �������� ������ ����
		if ( _info_header.height < 0 ) {
			#ifdef DB_DEBUG
			debug::get_instance( )->error( std::string( __FUNCTION__ ) + " -> info header: bottom - left origin unsupported\n" );
			#endif // DB_DEBUG
			file.close( );
			return 0;
		}

		// ��������� ������ ��� ������ ��������
		_data.resize( _info_header.width * _info_header.height * _info_header.bpp / 8 );

		// ��������, ����� �� ������������ �����
		if ( _info_header.width % 4 == 0 ) {
			// ������������ �� �����
			file.read( ( char* )_data.data( ), _data.size( ) );
			_header.file_size += static_cast< uint8_t >( _data.size( ) );
		} else {
			#ifdef DB_DEBUG
			debug::get_instance( )->message( std::string( __FUNCTION__ ) + " -> NEED ALIGNMENT\n" );
			#endif // DB_DEBUG
			// ������������ �����
			uint32_t row_stride = _info_header.width * _info_header.bpp / 8;
			uint32_t stride = row_stride;
			while ( stride % 4 != 0 )
				stride++;
			std::vector< uint8_t > padding_row( stride - row_stride );
			for ( int32_t i = 0; i < _info_header.height; i++ ) {
				file.read( ( char* )( _data.data( ) + row_stride * i ), row_stride );
				file.read( ( char* )padding_row.data( ), padding_row.size( ) );
			}
			_header.file_size += static_cast< uint32_t >( _data.size( ) ) + _info_header.height * static_cast< uint32_t >( padding_row.size( ) );
		}
		*/
		return 1;
	}

	// ����� ������ ����������� � ����
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

