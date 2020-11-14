#include "model_part.hpp"

namespace demonblade {

	model_part::model_part( mesh *mesh_ptr, texture *tex_ptr ) {
		// _texture
		_texture = tex_ptr;

		// _texture_name
		_texture_name = nullptr;
		if ( _texture )
			_texture_name = _texture->get_pointer( );

		// mesh
		_mesh = *mesh_ptr;
	}

	model_part::~model_part( void ) {
		// nope, no new's
	}

	bool model_part::is_data_valid( void ) {
		return ( _texture_name && _mesh.get_vertex_ptr( )->size( ) );
	}

	mesh* model_part::get_mesh_ptr( void ) {
		return &_mesh;
	}

	texture* model_part::get_texture_ptr( void ) {
		return _texture;
	}

	texture::texture_t* model_part::get_texture_name_ptr( void ) {
		return _texture_name;
	}
}	// namespace demonblade
