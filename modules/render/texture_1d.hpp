#ifndef TEXTURE_1D_HPP_INCLUDED
#define TEXTURE_1D_HPP_INCLUDED

#include "texture.hpp"
/*
	����� texture_1d ��������� ������ ���������� ��������. ���������� ����������: s( x )
	������������� ������ ��� �������� �������� �� RAM
*/

namespace demonblade {

	class texture_1d : public texture {

		public:

			texture_1d( void );

			~texture_1d( void );

			// ����� �������� 1d �������� �� ������
			// ��������� ��������� �� ������ � ��� ������ � ������
			bool load_from_memory(	const void *pixel_ptr, uint16_t width,
			                        image::img_sized_format_e sized = image::SIZED_RGB,
			                        tex_filter_e filter_high = NEAREST,
			                        tex_filter_e filter_low = NEAREST,
			                        tex_wrap_e wrap_s = CLAMP );

			// ����� ��������� ���������� ���������� ���������
			uint8_t get_tex_coords_num( void );

	};	// class texture_1d

}	// namespace demonblade
#endif // TEXTURE_1D_HPP_INCLUDED
