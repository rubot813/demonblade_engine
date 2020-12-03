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
		                        ogl::tex_base_format_e base = ogl::RGBA,
		                        ogl::tex_sized_format_e sized = ogl::RGBA8,
		                        ogl::tex_filter_e filter_high = ogl::NEAREST,
		                        ogl::tex_filter_e filter_low = ogl::NEAREST,
		                        ogl::tex_wrap_e wrap_u = ogl::CLAMP,
		                        ogl::tex_wrap_e wrap_v = ogl::CLAMP );

			// ����� ��������� ���������� ���������� ���������
			uint8_t get_tex_coords_num( void );

	};	// class texture_2d

}	// namespace demonblade
#endif // TEXTURE_2D_HPP_INCLUDED
