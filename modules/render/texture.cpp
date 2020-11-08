#include "texture.hpp"
#include "../common/gl_libs.hpp"
#include <iostream>

namespace demonblade {

	texture::texture( void ) {
		_texture_ptr = nullptr;
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
		_generate_and_apply_texture( );
		_apply_filter( );
		_apply_wrap( );
		return is_loaded( );
	}

	void texture::unload_from_vram( void ) {
		if ( is_loaded( ) )
			glDeleteTextures( 1, _texture_ptr );
	}

	bool texture::is_loaded( void ) {
		if ( _texture_ptr )
			return ( glIsTexture( *_texture_ptr ) == GL_TRUE );
		else
			return false;
	}

	texture::texture_t* texture::get_pointer( void ) {
		return ( is_loaded( ) ? _texture_ptr : nullptr );
	}

	void texture::_generate_and_apply_texture( void ) {

		// √енераци€ имени текстуры
		glGenTextures( 1, _texture_ptr );

		// ”становка текстуры ( все следующие операции будут производитьс€ над ней )
		glBindTexture( GL_TEXTURE_2D, *_texture_ptr );

		// «агрузка текстуры в VRAM
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

	void texture::_apply_filter( void ) {
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filter_high );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filter_low );
	}

	void texture::_apply_wrap( void ) {
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrap_u );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrap_v );
	}
}	// namespace demonblade
