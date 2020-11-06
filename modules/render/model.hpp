#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "./glm/glm.hpp"
#include "texture.hpp"
#include <sstream>
#include <fstream>
#include <vector>

// todo: render from container
// todo: i_drawable

namespace demonblade {
	// ����� ��������� ���� ������
	class model {

public:
	// ������ ����������� �� ���������
	model( void );

	// ����� �������� �������� ������, �������� � �������� �� Wavefront OBJ �����
	// ������ true � ������ ������
	bool load_from_obj( std::string file_name );

	// ����� ��������� �������� ��� ������
	// ������ true � ������ ������
	bool set_texture( texture::texture_t *tex );

	// ������ �����������, �������� � ��������������� ������
	inline void move( glm::vec3 offset );
	inline void rotate( glm::vec3 offset );
	inline void scale( glm::vec3 offset );

	// ������ ��������� �������, �������� � �������� ������
	inline void set_position( glm::vec3 value );
	inline void set_rotation( glm::vec3 value );
	inline void set_scale( glm::vec3 value );

	// ����� ��������� ������
	void render( void );

	// types, methods
	private:
		// ��������� �������� ����� ����������� ( ������������ )
		typedef struct {
			// ������� ������, �������� � ��������
			glm::uvec3 vertex;
			glm::uvec3 texel;
			glm::uvec3 normal;
		} _face_ind_s;

		// ������� ��������� ������: ���������, �������� � ���������������
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;

		// �������� ��������� ������
		glm::vec4 _ambient;		// ���������� ����
		glm::vec4 _diffuse;		// ��������� ����
		glm::vec4 _specular;	// ���������� ����

		// ������� ������
		std::vector< glm::vec3 > _vertex;

		// ������� ( ���������� ���������� ) ������
		std::vector< glm::vec2 > _texel;

		// ������� ������
		std::vector< glm::vec3 > _normal;

		// �������� ������
		texture::texture_t *_texture;

	};	// class model

}	// namespace demonblade

#endif // MODEL_HPP_INCLUDED
