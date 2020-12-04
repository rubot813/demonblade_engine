#ifndef BMP_HPP_INCLUDED
#define BMP_HPP_INCLUDED

#include <fstream>

#include "image.hpp"

/*
	����� ��������� �������� � bmp � dib �������
	����� - ������� image
*/

namespace demonblade {
	class bmp : public image {

		public:

#pragma pack(push, 1)
			// ��������� ��������� �����
			struct bmp_file_header_s {
				uint16_t file_type;		// ��� �����, ������ ����� 0x4D42
				uint32_t file_size;		// ������ ����� � ������
				uint32_t _reserved;		// ������ 32 ����
				uint32_t offset_data; 	// �������� ������ ������� ��������

				bmp_file_header_s( void ) {
					memset( this, 0, sizeof( bmp_file_header_s ) );
					file_type = 0x4D42;
				}
			};

			// ��������� ��������� ���������� � �����
			struct bmp_info_header_s {
				uint32_t	size;				// ������ ��������� ( bmp_info_header_s )  � ������
				int32_t		width;				// ������ ������� � ��������
				int32_t		height;				// ����� ������� � ��������
				// ���� > 0, ������ ������ � ������� ������ ����
				// ���� < 0, ������ ������ � �������� ������ ����

				uint16_t	planes;				// ���������� ���������� ������� �����. ������ = 1
				uint16_t	bpp;				// ���������� ��� �� �������
				uint32_t	compression;		// ������� ������ �����������. 0 ��� 24bpp, 3 ��� 32bpp
				uint32_t	image_size;

				int32_t		x_pix_per_meter;
				int32_t		y_pix_per_meter;
				uint32_t	used_color_ind;		// ���������� �������� ������ �� �������
				uint32_t	color_req;			// ���������� ������ ������������ � �����������. 0 - ��� �������

				bmp_info_header_s( void ) {
					memset( this, 0, sizeof( bmp_info_header_s ) );
					planes = 1;
				}
			};

			// ��������� ��������� ���������� � ����� �����
			struct bmp_color_header_s {
				uint32_t red_mask;			// �������� �����
				uint32_t green_mask;
				uint32_t blue_mask;
				uint32_t alpha_mask;
				uint32_t color_space_type;	// ��� ��������� ������������
				uint32_t _reserved[ 16 ];

				bmp_color_header_s( void ) {
					memset( this, 0, sizeof( bmp_color_header_s ) );
					red_mask			= 0x00ff0000;
					green_mask			= 0x0000ff00;
					blue_mask			= 0x000000ff;
					alpha_mask			= 0xff000000;
					color_space_type	= 0x73524742;	// spaceRGB
				}

				// ����� ���������� 1, ���� �������� ����� ����� ������ ������:
				// BGRA, sRGB
				// ����� ���������� 0
				bool is_valid_format( void );
			};
#pragma pack(pop)

			// default
			bmp( void );
			bmp( std::string file_name );
			~bmp( void );

			// ����� �������� ����������� �� �����
			bool load_from_file( std::string file_name );

			// ����� ������ ����������� � ����
			bool save_to_file( std::string file_name );

		private:

			// ��������� bmp �������
			bmp_file_header_s	_header;
			bmp_info_header_s	_info_header;
			bmp_color_header_s	_color_header;

	};	// class bmp

}	// namespace demonblade

#endif // BMP_HPP_INCLUDED
