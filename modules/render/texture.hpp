#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <cstdint>	// C++11

/*
	����� texture ��������� ���� ��������. ��������� ��������� ����� �������� �� RAM � VRAM
	����� ��� ������ �� ����� ������
*/

// todo: 1d, 3d textures, mipmap, check on 64bit compiler

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

				// ������ �������� � ��������� ��������
				CLAMP					= 0x2900,

				// ������ �������� � ��������� �������� � �����������
				MIRROR_CLAMP_TO_EDGE	= 0x8743,

				// ���������� ��������
				REPEAT					= 0x2901,

				// ��������� �������� � �����������
				MIRRORED_REPEAT			= 0x8370,

				// ������������� ��������, ��������� �� ��������
				CLAMP_TO_BORDER			= 0x812D,

				// ������������� ������� ��������, ��������� �� ����
				CLAMP_TO_EDGE			= 0x812E
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

			// ������ ����������� �� ���������
			texture( void );

			// ����������� � ������ ������� ����������
			// ��������� �������� � VRAM
			texture( const void *pixel_ptr, uint16_t width, uint16_t height, pack_e pack = RGBA8,
			         filter_e filter_high = NEAREST, filter_e filter_low = NEAREST,
			         wrap_e wrap_u = CLAMP, wrap_e wrap_v = CLAMP );

			~texture( void );

			// ��������� ����� ���������� ��������
			// filter_high	- ��� ���������� ����� ����������� �� ������ ������, ��� �� �������� ������
			// filter_low	- ��� ���������� ����� ����������� �� ������ ������, ��� �� �������� ������
			void set_filter_type( filter_e filter_high = NEAREST, filter_e filter_low = NEAREST );

			// ��������� ���� ��������� ��������
			// u � v - ���������� ���������� 2D, ����������� ������������� x, y
			void set_wrap_type( wrap_e wrap_u = CLAMP, wrap_e wrap_v = CLAMP );

			// ��������� ��������� �� ��������� ������ RGBA � �������� �������
			void set_pixel_pointer( const void *pixel_ptr, uint16_t width, uint16_t height );

			// ��������� ���� �������� ���� � �����������
			void set_pack_type( pack_e pack );

			// �������� �������� � ���������� � ���������� ����� �����������
			// ������ true � ������ �������� ��������
			bool load_to_vram( void );

			// �������� �������� �� ����������
			void unload_from_vram( void );

			// ����� ��������, ��������� �� �������� � VRAM
			bool is_loaded( void );

			// ����� ��������� ��������� �� ����������� ��������
			texture_t* get_pointer( void );

		private:

			// ���������� ������ �������� � OpenGL ��������� ����������
			void _generate_and_apply_texture( void );
			void _apply_filter( void );
			void _apply_wrap( void );

			// ��������� �� ������ ��������
			uint8_t		*_pixel_ptr;

			// ������� ������� �������. �������� ������ ����� _pixel_width * _pixel_height
			uint16_t	_pixel_width;
			uint16_t	_pixel_height;

			// ���� ���������� ��������
			filter_e _filter_high;
			filter_e _filter_low;

			// ���� ��������� �������� �� ����������� U, V
			wrap_e _wrap_u;
			wrap_e _wrap_v;

			// ��� �������� ���� ��� �������� ��������
			pack_e _pack;

			// ��������� �� ����������� ��������
			texture_t *_texture_ptr;

	};

}	// namespace demonblade
#endif // TEXTURE_HPP_INCLUDED
