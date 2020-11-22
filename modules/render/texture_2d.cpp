#include "texture_2d.hpp"
#include "../common/db_gl.hpp"

namespace demonblade {

	texture_2d::texture_2d( void ) {
		_type = ogl::TEXTURE_2D;
		_texture_ptr = 0;
	}

	texture_2d::~texture_2d( void ) {
		if ( _texture_ptr )
			glDeleteTextures( 1, &_texture_ptr );
	}

	bool texture_2d::load_from_memory( const void *pixel_ptr, uint16_t width, uint16_t height, pack_e pack,
	                                   filter_e filter_high, filter_e filter_low,
	                                   wrap_e wrap_u, wrap_e wrap_v ) {

		// ��������� ����� ��������: ������� � _texture_ptr ��� ��������������� ��������
		glGenTextures( 1, &_texture_ptr );

		// ��������� ��������
		bind( );

		// �������� �������� � VRAM
		glTexImage2D( _type,				// 2D
		              0,					// Mipmap level
		              pack,					// ��� �������� ���
		              width,				// ������
		              height,				// �����
		              0,					// �������� � ������� ����
		              GL_RGBA,				// ������ ��������
		              GL_UNSIGNED_BYTE,		// ������ ������
		              pixel_ptr );			// ��������� �� ������ ���� ��������

		// ��������� ���������� ���������� ��������
		glTexParameteri( _type, GL_TEXTURE_MAG_FILTER, filter_high );
		glTexParameteri( _type, GL_TEXTURE_MIN_FILTER, filter_low );

		// ��������� ���������� ��������� ��������
		glTexParameteri( _type, GL_TEXTURE_WRAP_S, wrap_u );
		glTexParameteri( _type, GL_TEXTURE_WRAP_T, wrap_v );

		return ( ( bool )_texture_ptr );
	}

	uint8_t texture_2d::get_tex_coords_num( void ) {
		return ( uint8_t )2;
	}
}	// namespace demonblade
