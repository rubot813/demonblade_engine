#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <cstdint>	// C++11

// todo: 1d, 3d textures, mipmap

namespace demonblade {
	// ����� ��������� ���� ��������
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
				CLAMP = 0x2900,

				// ������ �������� � ��������� �������� � �����������
				MIRROR_CLAMP_TO_EDGE = 8743,

				// ���������� ��������
				REPEAT =  0x2901,

				// ��������� �������� � �����������
				MIRRORED_REPEAT = 0x8370,

				// ������������� ��������, ��������� �� ��������
				CLAMP_TO_BORDER = 0x812D,

				// ������������� ������� ��������, ��������� �� ����
				CLAMP_TO_EDGE = 0x812E,
			};

			// ��� �������� DB. ��������� - �� ����� �������� �� 64��� �����������
			typedef uint32_t texture_t;

			// ������ ����������� �� ���������
			texture( void );

			// ����������� � ������ ������� ����������
			// ��������� �������� � VRAM
			texture( const uint8_t *pixel_ptr, uint16_t width, uint16_t height,
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

			// ��������� ��������� �� ��������� ������ RGBA ( �� 8 ��� �� ���������� ) � �������� �������
			void set_pixel_pointer( const uint8_t *pixel_ptr, uint16_t width, uint16_t height );

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

			// ��������� �� ����������� ��������
			texture_t *_texture_ptr;

	};

}	// namespace demonblade
#endif // TEXTURE_HPP_INCLUDED
