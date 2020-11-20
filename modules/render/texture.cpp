#include "texture.hpp"
#include "../common/db_gl.hpp"

namespace demonblade {

	texture::texture( void ) {
		#ifdef __linux__
		_texture_ptr = 0;
		#endif
	}

	texture::~texture( void ) {
		if ( _texture_ptr )
			glDeleteTextures( 1, &_texture_ptr );
	}

	bool texture::load_from_memory( const void *pixel_ptr, uint16_t width, uint16_t height, pack_e pack,
	                                filter_e filter_high, filter_e filter_low,
	                                wrap_e wrap_u, wrap_e wrap_v ) {

		// ��������� ����� ��������: ������� � _texture_ptr ��� ��������������� ��������
		glGenTextures( 1, &_texture_ptr );

		// ��������� �������� ( ��� ��������� �������� ����� ������������� ��� ��� )
		glBindTexture( GL_TEXTURE_2D, _texture_ptr );

		// �������� �������� � VRAM
		glTexImage2D( GL_TEXTURE_2D,
		              0,
		              pack,					// ��� �������� ���
		              width,				// ������
		              height,				// �����
		              0,
		              GL_RGBA,
		              GL_UNSIGNED_BYTE,
		              pixel_ptr );			// ��������� �� ������ ���� ��������

		// ��������� ��������� ���������� ��������
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_high );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_low );

		// ��������� ��������� ��������� ��������
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_u );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_v );

		return ( ( bool )_texture_ptr );
	}

	texture::texture_t* texture::get_pointer( void ) {
		return &_texture_ptr;
	}
}	// namespace demonblade
