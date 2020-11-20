#include "drawable.hpp"

namespace demonblade {

	// ==== OFFSETS ====
	void drawable::move( glm::vec3 offset ) {
		_position += offset;
	}
	void drawable::rotate( glm::vec3 offset ) {
		_rotation += offset;
	}
	void drawable::scale( glm::vec3 offset ) {
		_scale += offset;
	}
	// ====


	// ==== SETTERS ====
	void drawable::set_position( glm::vec3 value ) {
		_position = value;
	}
	void drawable::set_rotation( glm::vec3 value ) {
		_rotation = value;
	}
	void drawable::set_scale( glm::vec3 value ) {
		_scale = value;
	}
	// ====


	// ==== GETTERS ====
	glm::vec3 drawable::get_position( void ) {
		return _position;
	}
	glm::vec3 drawable::get_rotation( void ) {
		return _rotation;
	}
	glm::vec3 drawable::get_scale( void ) {
		return _scale;
	}
	// ====

	// ==== SETTERS ====
	void drawable::set_ambient( glm::vec4 value ) {
		_ambient = value;
	}
	void drawable::set_diffuse( glm::vec4 value ) {
		_diffuse = value;
	}
	void drawable::set_specular( glm::vec4 value ) {
		_specular = value;
	}
	// ====

	// ==== GETTERS ====
	glm::vec4 drawable::get_ambient( void ) {
		return _ambient;
	}
	glm::vec4 drawable::get_diffuse( void ) {
		return _diffuse;
	}
	glm::vec4 drawable::get_specular( void ) {
		return _specular;
	}
	// ====

}	// namespace demonblade
