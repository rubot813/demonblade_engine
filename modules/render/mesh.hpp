#ifndef MESH_HPP_INCLUDED
#define MESH_HPP_INCLUDED

#include "../common/db_glm.hpp"
#include "../common/global.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

/*
	����� ��������� ��� ( ������������� ����� ) ������
	��������� ��������� �������, ���������� ���������� � ����� �������� �� ������
	�������������� �������: Wavefront OBJ
	todo: milkshape 3d, md2 with anim
*/

namespace demonblade {

	class mesh {

		public:
			mesh( void );
			~mesh( void );
			void operator=( mesh &m );

			// ������� �����, �� �������� ����� ���� �������� ���
			typedef enum {
				UNKNOWN		= 0,	// ����������� ������
				OBJ					// Wavefront OBJ
			} format_e;

			// ����� �������� ���� �� �����, ���������� ������ �������������
			// � ������ ������ ������ true
			bool load_from_file( std::string file_name );

			// ��������� ������ ���� � ��������� ������� �����
			// � ������ ������ ������ true
			bool load_from_file( std::string file_name, format_e format );

			// ����� ���������� ��������� �� ��������� � ������������ ������
			std::vector< glm::vec3 >* get_vertex_ptr( void );

			// ����� ���������� ��������� �� ��������� � ����������� ������������
			std::vector< glm::vec2 >* get_texel_ptr( void );

			// ����� ���������� ��������� �� ��������� � ���������
			std::vector< glm::vec3 >* get_normal_ptr( void );

		private:

			// ����� ��������� ������� ����� �� ���� � ����
			format_e _get_extension( std::string *path );

			// ����� �������� ���� �� OBJ �����
			bool _load_obj( std::string fname );

			// types, methods
		private:
			// ��������� �������� ����� ����������� ( ������������ )
			typedef struct {
				// ������� ������, �������� � ��������
				glm::uvec3 vertex;
				glm::uvec3 texel;
				glm::uvec3 normal;
			} _face_ind_s;

			// �������
			std::vector< glm::vec3 > _vertex;

			// ������� ( ���������� ���������� )
			std::vector< glm::vec2 > _texel;

			// �������
			std::vector< glm::vec3 > _normal;

	};	// mesh class

}	// namespace demonblade

#endif // MESH_HPP_INCLUDED
