#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <cstdint>	// C++11
#ifndef __GNUC__	// For VC
	#include <cstddef>
#endif
#include "../core/ogl.hpp"

/*
	����� texture ��������� ������� ������ ��������
*/

namespace demonblade {

	class texture {

		public:

			// ������������ ����� ���������� ��������
			enum filter_e {
				NEAREST = 0x2600,		// ������������ �� �������� ��������
				LINEAR	= 0x2601		// ���������� ����������
			};

			// ������������ ����� ��������� ��������
			enum wrap_e {
				CLAMP					= 0x2900,	// ������ �������� � ��������� ��������
				MIRROR_CLAMP_TO_EDGE	= 0x8743,	// ������ �������� � ��������� �������� � �����������
				REPEAT					= 0x2901,	// ���������� ��������
				MIRRORED_REPEAT			= 0x8370,	// ��������� �������� � �����������
				CLAMP_TO_BORDER			= 0x812D,	// ������������� ��������, ��������� �� ��������
				CLAMP_TO_EDGE			= 0x812E	// ������������� ������� ��������, ��������� �� ����
			};

			// ������������ �������� �������� �������� ������ ��������
			// �� ������ ������ ���� ��������� ������ RGBA 8 / 32 ����
			enum pack_e {
				RGBA8			= 0x8058,	// RGBA, 8 ��� / �������
				RGBA8_SNORM		= 0xF897,	// RGBA, 8 �������� ��� / �������
				RGBA16			= 0x805B,	// RGBA, 16 ��� / �������
				SRGB8_ALPHA8	= 0x8C43,	// RGBA, 8 ��� / �������
				RGBA32F			= 0x8814,	// RGBA, 32 ��� � ��������� ������ / �������
				RGBA8I			= 0x8D8E,	// RGBA, 8i ��� / �������
				RGBA32I			= 0x8D82,	// RGBA, 32i ��� / �������
				RGBA32UI		= 0x8D70	// RGBA, 32ui ��� / �������
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
			texture_id _texture_ptr;

			// ��� ��������
			std::size_t		_type;

	};	// class texture

}	// namespace demonblade
#endif // TEXTURE_HPP_INCLUDED
