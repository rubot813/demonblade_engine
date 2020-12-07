#ifndef TEXTURE_2D_HPP_INCLUDED
#define TEXTURE_2D_HPP_INCLUDED

#include "texture.hpp"
/*
	����� texture_2d ��������� ���� ��������� ��������. ���������� : u ��� s(x), v ��� t(y)
	������������� ������ ��� �������� �������� �� RAM ��� ������ � VRAM � ��������
*/

namespace demonblade {

	class texture_2d : public texture {

		public:

			texture_2d( void );

			~texture_2d( void );

			// ����� �������� �������� �� ������
			// ��������� ��������� �� ������ � ��� ������ � �����
			bool load_from_memory(	const void *pixel_ptr, uint16_t width, uint16_t height,
			                        image::img_sized_format_e sized = image::SIZED_RGB,
			                        tex_filter_e filter_high = NEAREST,
			                        tex_filter_e filter_low = NEAREST,
			                        tex_wrap_e wrap_u = CLAMP,
			                        tex_wrap_e wrap_v = CLAMP );

			// ����� �������� �������� �� �����������
			bool load_from_image(	image *img,
			                        tex_filter_e filter_high = NEAREST,
			                        tex_filter_e filter_low = NEAREST,
			                        tex_wrap_e wrap_u = CLAMP,
			                        tex_wrap_e wrap_v = CLAMP );

			// ����� ��������� ���������� ���������� ���������
			uint8_t get_tex_coords_num( void );

	};	// class texture_2d

}	// namespace demonblade
#endif // TEXTURE_2D_HPP_INCLUDED
