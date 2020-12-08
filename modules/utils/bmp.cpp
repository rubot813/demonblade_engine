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

		// ������ ��������� �����
		file->read( ( char* )&_file_header, sizeof( bmp_file_header_s ) );
		db_dbg_msg( "file_header.type = " + std::to_string( _file_header.type ) + "\n" );
		db_dbg_msg( "file_header.size = " + std::to_string( _file_header.size ) + " bytes\n" );

		// �������� ���� �����
		if ( _file_header.type != 0x4D42 ) {
			db_dbg_error( "file header -> wrong type. big endian?\n" );
			return 0;
		}

		// ������ ��������� ���������� � �����

		// ������ �������� ��� ������ CORE
		file->read( ( char* )&_info_header, BMP_INFO_HEADER_SIZE_CORE + 4 );	// ���� size �� ����������� � �������, ������� +4 �����
		db_dbg_msg( "info_header.header size = " + std::to_string( _info_header.size ) + " bytes\n" );
		db_dbg_msg( "info_header.width = " + std::to_string( _info_header.width ) + "\n" );
		db_dbg_msg( "info_header.height = " + std::to_string( _info_header.height ) + "\n" );
		db_dbg_msg( "info_header.bpp = " + std::to_string( _info_header.bpp ) + "\n" );

		// �������� ������������ ������� �����: ������ ������ ���� � �������� ������ ����
		if ( _info_header.height < 0 || _info_header.width < 0 ) {
			db_dbg_error( "info header -> bottom - left origin unsupported\n" );
			return 0;
		}

		// ��������� ������ bmp
		bmp_info_header_s::version_s version = _info_header.get_version( );
		switch( version ) {
			case bmp_info_header_s::VERSION_CORE: {
				db_dbg_msg( "info_header.version = CORE\n" );
				break;
			}

			case bmp_info_header_s::VERSION_3: {
				db_dbg_msg( "info_header.version = 3\n" );

				// �������� ���������� ����� ��������� bmp_info_header
				file->read( ( char* )&_info_header + BMP_INFO_HEADER_SIZE_CORE + 4,
				            BMP_INFO_HEADER_SIZE_V3 - BMP_INFO_HEADER_SIZE_CORE + 4 );

				break;
			}

			case bmp_info_header_s::VERSION_4: {
				db_dbg_msg( "info_header.version = 4\n" );

				// �������� ���������� ����� ��������� bmp_info_header
				file->read( ( char* )&_info_header + BMP_INFO_HEADER_SIZE_CORE + 4,
				            BMP_INFO_HEADER_SIZE_V3 - BMP_INFO_HEADER_SIZE_CORE + 4 );	// V3 - ���������

				// �������� bmp_color_header_s
				file->read( ( char* )&_color_header, sizeof( bmp_color_header_s ) );
				db_dbg_msg( "color_header.red_mask =  " + std::to_string( _color_header.red_mask ) );
				db_dbg_msg( "color_header.green_mask =  " + std::to_string( _color_header.green_mask ) );
				db_dbg_msg( "color_header.blue_mask =  " + std::to_string( _color_header.blue_mask ) );
				db_dbg_msg( "color_header.alpha_mask =  " + std::to_string( _color_header.alpha_mask ) );

				// �������� ��������� ����� ����� BGRA � ��������� ������������ sRGB
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

		// �������� �������� ��� ������ 3+, ����� �� �����������
		if ( version >= bmp_info_header_s::VERSION_3 ) {
			db_dbg_msg( "info_header.compression = " + std::to_string( _info_header.compression ) + "\n" );
			db_dbg_msg( "info_header.palette color used = " + std::to_string( _info_header.used_color_ind ) + "\n" );
			db_dbg_msg( "info_header.colors = " + std::to_string( _info_header.color_req ) + "\n" );

			// �������� ��������� ���� ������ �����������
			bmp_info_header_s::compression_s comp = _info_header.get_compression( );
			if (	comp != bmp_info_header_s::CMP_BI_RGB &&
			        comp != bmp_info_header_s::CMP_BI_BITFIELDS &&
			        comp != bmp_info_header_s::CMP_BI_APHABITFIELS ) {
				db_dbg_error( "info header -> unsupported compression format\n" );
				return 0;
			}
		}

		// ��������� �������� �����������
		_width	= _info_header.width;
		_height = _info_header.height;

		// ��������� ������������ ������� �����
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

		// ������ ������� � ������ ( 3 ��� 4 )
		uint8_t pixel_size = _info_header.bpp / 8;

		// ������ ���� �������� � ������
		uint16_t row_size = _width * pixel_size;

		// aka row_padding. �������� ���� � ����� ������ ������ ������� ����� ����������,
		// �.�. ����� ������ ������ ���� ������ 4 ������
		uint16_t row_indent = ( ( _width * pixel_size ) % 4 ) & 3;
		db_dbg_msg( "width = " + std::to_string( _width * pixel_size ) + "\n" );
		db_dbg_msg( "row_indent = " + std::to_string( row_indent ) + "\n" );
		db_dbg_msg( "total = " + std::to_string( ( _width * pixel_size ) + row_indent ) + "\n" );

		// ������� � ������� ��������
		file->seekg( _file_header.offset_data, file->beg );

		// ��������� ������ ��� ������ ��������
		_data.resize( _width * _height * pixel_size );

		// �������� ��� ����� ��������
		uint32_t row_offset = 0;
		for ( uint32_t h = 0; h < _height; h++ ) {
			// ���������� ���� ��������
			file->read( ( char* )_data.data( ) + row_offset, row_size );

			// �������� ������ � _data, �� �������� ����������� �������
			row_offset += row_size;

			// ������� ���������� ���� � ����� ������� ����, ���� ���������� ( ���� ������ % 4 != 0 )
			//file->seekg( 3, std::ios_base::cur );
		}

		return 1;
	}

	bool bmp::load_from_file( std::string file_name ) {

		// �������� �����
		std::ifstream file;
		file.open( file_name, std::ios_base::binary );
		if ( !file.is_open( ) ) {
			db_dbg_error( "cannot open file\n" );
			return 0;
		}

		// ������ ����������
		if ( !_read_header( &file ) ) {
			db_dbg_error( "error while reading headers\n" );
			file.close( );
			return 0;
		}

		// ������ ����������
		if ( !_read_pixel_data( &file ) ) {
			db_dbg_error( "error while reading pixel data\n" );
			file.close( );
			return 0;
		}

		// ����������� BGR -> RGB / BGRA -> RGBA
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
			case BMP_INFO_HEADER_SIZE_CORE: {
				ver = VERSION_CORE;
				break;
			}
			case BMP_INFO_HEADER_SIZE_V3: {
				ver = VERSION_3;
				break;
			}
			case BMP_INFO_HEADER_SIZE_V4: {
				ver = VERSION_4;
				break;
			}
			case BMP_INFO_HEADER_SIZE_V5: {
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

