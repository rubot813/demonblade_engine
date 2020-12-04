#ifndef IMAGE_HPP_INCLUDED
#define IMAGE_HPP_INCLUDED

#include <vector>
#include <cstring>

#include "../common/global.hpp"
#include "../core/ogl.hpp"

/*
	image - ������� ����� ��� �����������. ��������� ������ ��� �������� ����������� �� ������ � RAM,
	������ ����������� �� ������� ����. ��� ������ - ���������� ��������� ��������� ������ � �����������
	��������� ������. ����� ������������ ������ � ������������� ��� ����� ������ ( ��� ������������ ) �
	� ������������� � ����� ������� ( � ������������� )

	����������� �����������:
	������ ������� RGB / BGR / RGBA / BGRA ( 24 / 32 ���� �� ������� )
	�������� ������������ sRGB
	��� ������� TGA �������������� ������ ( ����������� RLE )
	������ ����������� - ����� ������� ����
*/

namespace demonblade {

	class image {

		public:

			// Empty by default
			image( void );
			~image( void );

			// ������������ ������� �������� �������� ��������
			enum img_base_format_e {
				BASE_RGB	= 0x1907,	// R G B
				BASE_RGBA	= 0x1908	// R G B A
			};

			// ������������ ����������� �������� �������� ��������
			enum img_sized_format_e {
				SIZED_RGB	= 0x8051,	// RGB, 8 ��� / �������
				SIZED_RGBA	= 0x8058,	// RGBA, 8 ��� / �������
				SIZED_BGR	= 0x80E0,	// BGR,	8 ��� / �������
				SIZED_BGRA 	= 0x80E1	// BGRA, 8 ��� / �������
			};

			// ����� �������� ����������� �� �����
			virtual bool load_from_file( std::string file_name ) = 0;

			// ����� ������ ����������� � ����
			virtual bool save_to_file( std::string file_name ) = 0;

			// ����� ��������� ��������� �� ������ ��������
			void* get_data_ptr( void );

			// ����� ��������� ������� �������� �������� ( ������������ )
			img_sized_format_e get_pixel_format( void );

			// ����� ��������� ������� �������� �������� ( �������� )
			img_base_format_e get_base_pixel_format( void );

			// ����� ��������� ������������ ������� �������� �������� �� ��������
			static img_base_format_e get_base_pixel_format( img_sized_format_e sized );

			// ������ ��������� �������� �����������
			uint16_t get_width( void );		// ������
			uint16_t get_height( void );	// ������

			// ����� ���������� ���������� ��� �� ������� ( bpp )
			// ������ 0 � ������ ������
			uint8_t get_bpp( void );

			// ����� ���������� ������ ������� ������ ��������
			// ����� ���� ����������� ��� �������� ������ ����� ������
			// �������� ����������� �� ������������
			uint32_t get_data_size( void );

			// ����� ���������� ���������� �������� � �����������
			// ������ 0 � ������ ������
			uint32_t get_pixel_count( void );

			// ����� ��������������� ������������ ������� �������� �������� �����������
			// �������� ������ -> ���������������� ������
			// RGB -> BGR
			// RGBA -> BGRA
			// BGR -> RGB
			// BGRA -> RGBA
			// ������ 1 � ������ ������
			// ������ 0 � ������ ������
			bool convert_format( void );

		private:

			// ������ ��������
			std::vector< uint8_t >	_data;

			// ������� ����������� � ��������
			uint32_t	_width;
			uint32_t	_height;

			// ������ �����������
			img_sized_format_e	_format;
	};

}	// namespace demonblade

#endif // IMAGE_HPP_INCLUDED
