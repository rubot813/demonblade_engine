#include "texture_1d.hpp"
#include "../common/db_gl.hpp"

namespace demonblade {

	texture_1d::texture_1d( void ) {
		_type = ogl::TEXTURE_1D;
		_texture_ptr = 0;
	}

	texture_1d::~texture_1d( void ) {
		if ( _texture_ptr )
			glDeleteTextures( 1, &_texture_ptr );
	}

	bool texture_1d::load_from_memory(	const void *pixel_ptr, uint16_t width,
	                                    ogl::tex_base_format_e base,
	                                    ogl::tex_sized_format_e sized,
	                                    ogl::tex_filter_e filter_high,
	                                    ogl::tex_filter_e filter_low,
	                                    ogl::tex_wrap_e wrap_s ) {

		// ��������� ����� ��������: ������� � _texture_ptr ��� ��������������� ��������
		glGenTextures( 1, &_texture_ptr );

		// ��������� ��������
		bind( );

		// �������� �������� � VRAM
		glTexImage1D( _type,				// 1D
		              0,					// Mipmap level
		              sized,				// ��� �������� ���
		              width,				// ������
		              0,					// �������� � ������� ����
		              base,					// ������ ��������
		              GL_UNSIGNED_BYTE,		// ������ ������
		              pixel_ptr );			// ��������� �� ������ ���� ��������

		// ��������� ���������� ���������� ��������
		glTexParameteri( _type, GL_TEXTURE_MAG_FILTER, filter_high );
		glTexParameteri( _type, GL_TEXTURE_MIN_FILTER, filter_low );

		// ��������� ��������� ��������� ��������
		glTexParameteri( _type, GL_TEXTURE_WRAP_S, wrap_s );

		return ( ( bool )_texture_ptr );
	}

	uint8_t texture_1d::get_tex_coords_num( void ) {
		return ( uint8_t )1;
	}
}	// namespace demonblade
