#include "mesh.hpp"

namespace demonblade {

	mesh::mesh( void ) {

	}

	mesh::~mesh( void ) {

	}

	void mesh::operator=( mesh &m ) {
		_vertex			= *( m.get_vertex_ptr( ) );
		_texel			= *( m.get_texel_ptr( ) );
		_normal			= *( m.get_normal_ptr( ) );
	}

	std::vector< glm::vec3 >* mesh::get_vertex_ptr( void ) {
		return &_vertex;
	}

	std::vector< glm::vec2 >* mesh::get_texel_ptr( void ) {
		return &_texel;
	}

	std::vector< glm::vec3 >* mesh::get_normal_ptr( void ) {
		return &_normal;
	}

}	// namespace demonblade
