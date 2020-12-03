#ifndef TEXTURE_3D_HPP_INCLUDED
#define TEXTURE_3D_HPP_INCLUDED

#include "texture.hpp"
/*
	����� texture_3d ��������� ���� ���������� ��������. ���������� : s(x), t(y), r(z)
	������������� ������ ��� �������� �������� �� RAM ��� ������ � VRAM � ��������
*/

namespace demonblade {

	class texture_3d : public texture {

		public:

			texture_3d( void );

			~texture_3d( void );

			// ����� �������� �������� �� ������
			// ��������� ��������� �� ������ � ��� ������, ����� � �������
			// ���� ��� ������ ������� �������, �� ��� ������ ��������
			bool load_from_memory( 	const void *pixel_ptr, uint16_t width, uint16_t height, uint16_t depth,
									ogl::tex_base_format_e base = ogl::RGBA,
									ogl::tex_sized_format_e sized = ogl::RGBA8,
									ogl::tex_filter_e filter_high = ogl::NEAREST,
									ogl::tex_filter_e filter_low = ogl::NEAREST,
									ogl::tex_wrap_e wrap_s = ogl::CLAMP,
									ogl::tex_wrap_e wrap_t = ogl::CLAMP,
									ogl::tex_wrap_e wrap_r = ogl::CLAMP  );

			// ����� ��������� ���������� ���������� ���������
			uint8_t get_tex_coords_num( void );

	};	// class texture_3d

}	// namespace demonblade
#endif // TEXTURE_3D_HPP_INCLUDED
