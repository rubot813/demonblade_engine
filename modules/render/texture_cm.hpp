#ifndef TEXTURE_CM_HPP_INCLUDED
#define TEXTURE_CM_HPP_INCLUDED

#include "texture.hpp"
/*
	����� texture_cm ��������� ���� ���������� ��������. ���������� : s(x), t(y), r(z)
	������������� ������ ��� �������� �������� �� RAM ��� ������ � VRAM � ��������
*/

namespace demonblade {

	class texture_cm : public texture {

		public:

			texture_cm( void );

			~texture_cm( void );
/*
			// ����� �������� �������� �� ������
			// ��������� ��������� �� ������ � ��� ������ � �����
			bool load_from_memory( const void *pixel_ptr, uint16_t width, uint16_t height, pack_e pack = RGBA8,
			                       filter_e filter_high = NEAREST, filter_e filter_low = NEAREST,
			                       wrap_e wrap_u = CLAMP, wrap_e wrap_v = CLAMP );
*/
			// ����� ��������� ���������� ���������� ���������
			uint8_t get_tex_coords_num( void );

	};	// class texture_cm

}	// namespace demonblade
#endif // TEXTURE_CM_HPP_INCLUDED
