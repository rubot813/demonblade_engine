#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "model_part.hpp"

#include <sstream>
#include <list>

/*
	�����, ����������� ������������ �������� � �������� � ���������� ������ ��������.
	������ ������� �� ������ ( part ). ����� ������ ������� �� ���� ( ��������� ) � ��������.
*/

// todo: render from container
// todo: i_drawable

namespace demonblade {
	// ����� ��������� ���� ������
	class model {

		public:
			model( void );
			~model( void );

			// ����� ���������� �������� � ���� ������
			// ����������� � ������ � ���� �����
			// ������ true ���� ��� ��������� � ������� ( ������ � ��������� )
			// ������ false ���� �� ������� ������,
			// ���� ��������� �� �������,
			// ���� ��� �� �������� � RAM,
			// ���� �������� �� ��������� � VRAM
			bool add_part( mesh *mesh_ptr, texture *tex_ptr );

			// ����� �������� ����� ������ �� id
			// ������ true ���� �������
			// ������ false ���� ����� �� ���������� ��� out of range
			bool remove_part( std::size_t id );

			// ����� ��������� ���������� ������ ������
			std::size_t get_part_count( void );

			// ������ ��������� ���������� �� ��� � �������� ������
			// ��������� ���������� ����� ����� ������
			mesh*		get_mesh( std::size_t id );
			texture*	get_texture( std::size_t id );

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

			// ����� ��������� ���� ������ ��� �� �����
			void render( void );
			void render( std::size_t id );

		private:

			// ���������� ����� ��������� ����� ������ ����� ���������
			void _render( model_part *part_ptr );

			// ����� ��������� ��������� �� ������� model_part �� �������
			// ���� ������ std::list::at
			std::list< model_part >::iterator _get_part_iterator( std::size_t index );

			// ������� ��������� ������: ���������, �������� � ���������������
			glm::vec3 _position;
			glm::vec3 _rotation;
			glm::vec3 _scale;

			// �������� ��������� ������
			glm::vec4 _ambient;		// ���������� ����
			glm::vec4 _diffuse;		// ��������� ����
			glm::vec4 _specular;	// ���������� ����

			// ��������� � ������� ������
			std::list< model_part > _part;

	};	// class model

}	// namespace demonblade

#endif // MODEL_HPP_INCLUDED
