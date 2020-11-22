#include "texture.hpp"
#include "../common/db_gl.hpp"

namespace demonblade {

	void texture::bind( void ) {
		glBindTexture( _type, _texture_ptr );	// oh, how fast
	}

	texture::texture_id* texture::get_pointer( void ) {
		return &_texture_ptr;
	}
}	// namespace demonblade
