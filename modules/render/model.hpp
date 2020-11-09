#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "../common/gl_libs.hpp"
#include "texture.hpp"
#include "mesh.hpp"

#include <sstream>
#include <fstream>
#include <vector>

/*
	�����, ����������� ������������ �������� � �������� ������ ��������
	�����! ���������� �������� � ������, ������ �������������:

	�������������:
	// ====
	db::texture tex;
    db::mesh mesh;
    db::model *m
    m = new db::model( &mesh, &tex );
    ...
    delete m;	// ����� �� �� ������� tex � mesh
    // ====

    db::model m( new db::mesh( ... ), new db::texture( ... ) );

    // ====

    db::texture tex;
    db::mesh mesh;

    db::model m;
    m.set_texture( &tex )
    m.set_mesh( &mesh )

	// ====
*/

// todo: render from container
// todo: i_drawable

namespace demonblade {
	// ����� ��������� ���� ������
	class model {

		public:
			// ������ ����������� �� ���������
			model( void );

			// ����������� � ����������� �� ������� ����������� ��� � ����������� ��������
			model( mesh *msh, texture *tex );

			// ����������� � ��������� ���������� �������� � ���������� ����
			model( mesh msh, texture tex );

			~model( void );

			// ����� ��������� �������� ��� ������ � ���� ������
			// ������ true � ������ ������
			bool set_texture( texture *tex );
			bool set_mesh( mesh *msh );

			// ������ ��������� ���������� �� �������� � ��� ������
			texture*	get_texture( void );
			mesh*		get_mesh( void );

			// ������ �����������, �������� � ��������������� ������
			void move( glm::vec3 offset );
			void rotate( glm::vec3 offset );
			void scale( glm::vec3 offset );

			// ������ ��������� �������, �������� � �������� ������
			void set_position( glm::vec3 value );
			void set_rotation( glm::vec3 value );
			void set_scale( glm::vec3 value );

			// ������ ��������� �������, �������� � �������� ������
			glm::vec3 get_position( void );
			glm::vec3 get_rotation( void );
			glm::vec3 get_scale( void );

			// ����� ��������� ������
			void render( void );

		private:

			// ������� ��������� ������: ���������, �������� � ���������������
			glm::vec3 _position;
			glm::vec3 _rotation;
			glm::vec3 _scale;

			// �������� ��������� ������
			glm::vec4 _ambient;		// ���������� ����
			glm::vec4 _diffuse;		// ��������� ����
			glm::vec4 _specular;	// ���������� ����

			// ��������� �� ����������� �������� � VRAM
			texture::texture_t	*_texture_vram;

			// ��������� �� ��������� ������ �������
			texture				*_texture;

			// ��������� �� ��������� ������ ������ � �����
			mesh				*_mesh;

			// �����, ��� �� ��������� ��������� ���� ��� ��������
			// ������������ � ������������ ����� ���������� ������
			bool _mesh_allocated;
			bool _tex_allocated;

	};	// class model

}	// namespace demonblade

#endif // MODEL_HPP_INCLUDED
