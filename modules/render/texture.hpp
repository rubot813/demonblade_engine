#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <cstdint>	// C++11
#ifndef __GNUC__	// For VC
	#include <cstddef>
#endif
#include "../core/ogl.hpp"
#include "../utils/image.hpp"

/*
	����� texture ��������� ������� ������ ��������
*/

namespace demonblade {

	class texture {

		public:

			// ������������ ����� ���������� ��������
			enum tex_filter_e {
				NEAREST = 0x2600,		// ������������ �� �������� ��������
				LINEAR	= 0x2601		// ���������� ����������
			};

			// ������������ ����� ��������� ��������
			enum tex_wrap_e {
				CLAMP					= 0x2900,	// ������ �������� � ��������� ��������
				MIRROR_CLAMP_TO_EDGE	= 0x8743,	// ������ �������� � ��������� �������� � �����������
				REPEAT					= 0x2901,	// ���������� ��������
				MIRRORED_REPEAT			= 0x8370,	// ��������� �������� � �����������
				CLAMP_TO_BORDER			= 0x812D,	// ������������� ��������, ��������� �� ��������
				CLAMP_TO_EDGE			= 0x812E	// ������������� ������� ��������, ��������� �� ����
			};

			// ����� ��������, ����� �� ������� GLuint
			typedef std::size_t texture_id;

			// ����� ��������� ��������
			void bind( void );

			// ����� ��������� ���������� ���������� ���������
			virtual uint8_t get_tex_coords_num( void );

			// ����� ��������� ��������� �� ������������� ���������� ��������
			texture_id* get_pointer( void );

		protected:

			// ������������� ����������� ��������
			texture_id	_texture_ptr;

			// ��� ��������
			std::size_t	_type;

	};	// class texture

}	// namespace demonblade
#endif // TEXTURE_HPP_INCLUDED
