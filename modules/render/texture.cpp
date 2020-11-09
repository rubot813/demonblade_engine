#include "texture.hpp"
#include "../common/gl_libs.hpp"
#include <iostream>

namespace demonblade {

	texture::texture( void ) {
		_texture_ptr = nullptr;
		_filter_high	= NEAREST;
		_filter_low		= NEAREST;
		_wrap_u			= CLAMP;
		_wrap_v			= CLAMP;
		_pack			= RGBA8;
	}

	texture::texture( const void *pixel_ptr, uint16_t width, uint16_t height, pack_e pack,
	                  filter_e filter_high, filter_e filter_low,
	                  wrap_e wrap_u, wrap_e wrap_v ) {
		_pixel_ptr		= _pixel_ptr;
		_pixel_width	= width;
		_pixel_height	= height;
		_filter_high	= filter_high;
		_filter_low		= filter_low;
		_wrap_u			= wrap_u;
		_wrap_v			= wrap_v;
		_pack			= pack;
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

	void texture::set_pixel_pointer( const void *pixel_ptr, uint16_t width, uint16_t height ) {
		_pixel_ptr = _pixel_ptr;
		_pixel_width = width;
		_pixel_height = height;
	}

	bool texture::load_to_vram( void ) {
		_generate_and_apply_texture( );
		_apply_filter( );
		_apply_wrap( );
		return ( _texture_ptr != nullptr );
	}

	void texture::unload_from_vram( void ) {
		if ( _texture_ptr )
			glDeleteTextures( 1, _texture_ptr );
	}

	bool texture::is_loaded( void ) {
		return ( _texture_ptr != nullptr );
	}

	texture::texture_t* texture::get_pointer( void ) {
		return _texture_ptr;
	}

	void texture::_generate_and_apply_texture( void ) {

		// √енераци€ имени текстуры
		glGenTextures( 1, _texture_ptr );

		// ”становка текстуры ( все следующие операции будут производитьс€ над ней )
		glBindTexture( GL_TEXTURE_2D, *_texture_ptr );

		// «агрузка текстуры в VRAM
		glTexImage2D( GL_TEXTURE_2D,
		              0,
		              _pack,
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
