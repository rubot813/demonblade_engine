#include "texture.hpp"
#include "../common/include_gl.hpp"

namespace demonblade {

	texture::texture( void ) {
		// nope
		// DOPE
	}

	texture::texture( const uint8_t *pixel_ptr, uint16_t width, uint16_t height,
			filter_e filter_high, filter_e filter_low,
			wrap_e wrap_u, wrap_e wrap_v ) {
		_pixel_ptr		= _pixel_ptr;
		_pixel_width	= width;
		_pixel_height	= height;
		_filter_high	= filter_high;
		_filter_low		= filter_low;
		_wrap_u			= wrap_u;
		_wrap_v			= wrap_v;
		load_to_vram( );
	}

	texture::~texture( void ) {
		unload_from_vram( );
	}

	void texture::set_filter_type( filter_e filter_high, filter_e filter_low ) {
		_filter_high	= filter_high;
		_filter_low		= filter_low;
	}

	void texture::set_wrap_type( wrap_e wrap_u, wrap_e wrap_v ) {
		_wrap_u = wrap_u;
		_wrap_v = wrap_v;
	}

	void texture::set_pixel_pointer( const uint8_t *pixel_ptr, uint16_t width, uint16_t height ) {
		_pixel_ptr = _pixel_ptr;
		_pixel_width = width;
		_pixel_height = height;
	}

	bool texture::load_to_vram( void ) {
		generate_and_apply_texture( );
		apply_filter( );
		apply_wrap( );
		return is_loaded( );
	}

	void texture::unload_from_vram( void ) {
		if ( is_loaded( ) )
			glDeleteTextures( 1, _texture_ptr );
	}

	bool texture::is_loaded( void ) {
		return ( glIsTexture( *_texture_ptr ) == GL_TRUE );
	}

	texture::texture_t* texture::get_pointer( void ) {
		return ( is_loaded( ) ? _texture_ptr : nullptr );
	}

	void texture::generate_and_apply_texture( void ) {

		// Генерация имени текстуры
		glGenTextures( 1, _texture_ptr );

		// Установка текстуры ( все следующие операции будут производиться над ней )
		glBindTexture( GL_TEXTURE_2D, *_texture_ptr );

		// Передача изображения
		glTexImage2D( GL_TEXTURE_2D,
		              0,
		              GL_RGBA8,
		              _pixel_width,
		              _pixel_height,
		              0,
		              GL_RGBA,
		              GL_UNSIGNED_BYTE,
		              _pixel_ptr );
	}

	void texture::apply_filter( void ) {
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filter_high );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filter_low );
	}

	void texture::apply_wrap( void ) {
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrap_u );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrap_v );
	}
}	// namespace demonblade
