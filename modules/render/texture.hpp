#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <cstdint>	// C++11

/*
	����� texture ��������� ���� ��������. ��������� ��������� ����� �������� �� RAM � VRAM

	usage:
	db::texture *tex;
	tex = new db::texture;
	if ( tex.load_from_memory( ... ) ) {
		// ok!
	}
	model->set_texture( tex );
*/

// todo: 1d, 3d textures, mipmap, check on 64bit compiler

namespace demonblade {

	class texture {

		public:
			texture( void );
			~texture( void );

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

			// ����� ��������
			typedef std::size_t texture_t;

			// ����� � ������ ������� ����������
			// ��������� �������� � VRAM
			bool load_from_memory( const void *pixel_ptr, uint16_t width, uint16_t height, pack_e pack = RGBA8,
			                       filter_e filter_high = NEAREST, filter_e filter_low = NEAREST,
			                       wrap_e wrap_u = CLAMP, wrap_e wrap_v = CLAMP );

			// ����� ��������� ����� ���������� ��������, ������������ � db::model
			texture_t* get_pointer( void );

		private:

			// ��������� �� ����������� ��������
			texture_t _texture_ptr;
	};	// class texture

}	// namespace demonblade
#endif // TEXTURE_HPP_INCLUDED
