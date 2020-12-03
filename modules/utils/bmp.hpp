#ifndef BMP_HPP_INCLUDED
#define BMP_HPP_INCLUDED

#include <vector>
#include <fstream>

#include "../common/global.hpp"
#include "bmp.hpp"

/*
	����� ��������� ������, ������������� � ��������� BMP �����
*/

namespace demonblade {
	class bmp {

		public:

#pragma pack(push, 1)
			// ��������� ��������� bmp �����
			struct bmp_header_s {
				uint16_t file_type;		// ��� �����, ������ ����� 0x4D42
				uint32_t file_size;		// ������ ����� � ������
				uint32_t _reserved;		// ������ 32 ����
				uint32_t offset_data; 	// �������� ������ ������� ��������
				bmp_header_s( void ) {
					#ifdef __linux
					memset( this, 0, sizeof( bmp_header_s ) );
					#endif
					file_type = 0x4D42;
				}
			};

			struct bmp_info_header_s {
				uint32_t	size;				// ������ ��������� ( bmp_info_header_s )  � ������
				int32_t		width;				// ������ ������� � ��������
				int32_t		height;				// ����� ������� � ��������
				// ���� > 0, ������ ������ � ������� ������ ����
				// ���� < 0, ������ ������ � �������� ������ ����

				uint16_t	planes;				// ���������� ���������� ������� �����. ������ = 1
				uint16_t	bpp;				// ���������� ��� �� �������
				uint16_t	compression;		// ������� ������ �����������. 0 ��� 24bpp, 3 ��� 32bpp
				uint32_t	image_size;

				int32_t		x_pix_per_meter;
				int32_t		y_pix_per_meter;
				uint32_t	used_color_ind;		// ���������� �������� ������ �� �������
				uint32_t	color_req;			// ���������� ������ ������������ � �����������. 0 - ��� �������
				bmp_info_header_s( void ) {
					#ifdef __linux
					memset( this, 0, sizeof( bmp_info_header_s ) );
					#endif
					planes = 1;
				}
			};

			struct bmp_color_header_s {
				uint32_t red_mask;			// �������� �����
				uint32_t green_mask;
				uint32_t blue_mask;
				uint32_t alpha_mask;
				uint32_t color_space_type;	// ��� ��������� ������������
				uint32_t _reserved[ 16 ];

				bmp_color_header_s( void ) {
					#ifdef __linux
					memset( this, 0, sizeof( bmp_color_header_s ) );
					#endif
					red_mask			= 0x00ff0000;
					green_mask			= 0x0000ff00;
					blue_mask			= 0x000000ff;
					alpha_mask			= 0xff000000;
					color_space_type	= 0x73524742;	// spaceRGB
				}

				// ����� ���������� 1, ���� ������ �������� � ������� BGRA � �������� ������������ sRGB
				// ����� ���������� 0
				bool is_correct_type( void );

			};

#pragma pack(pop)

			bmp( void );
			bmp( std::string file_name );

			~bmp( void );

			// �������������� ������

			// ������ ������� �� �����
			bool read( std::string file_name );

			// ������ ������� � ����
			bool write( std::string file_name );

			// �������� � ������ ������� �������� ��������, � ������ ����� - ������
			bool create( uint16_t width, uint16_t height, bool alpha = 1 );

			// ��������, ����� �� ��������� ������ ������ ��������
			// ����� ���� ����������� ��� �������� ������ ����� ������ �� ������������
			bool is_empty( void );

			// ����� ��������� ��������� �� ������ ��������
			void *get_data_ptr( void );

			// ������ ��������� �������� �����������
			int32_t get_width( void );
			int32_t get_height( void );

		private:

			// ���������
			bmp_header_s		_header;
			bmp_info_header_s	_info_header;
			bmp_color_header_s	_color_header;

			// ��������� ������������ ������� ��������
			std::vector< uint8_t > _data;
	};	// class bmp

}	// namespace demonblade

#endif // BMP_HPP_INCLUDED
