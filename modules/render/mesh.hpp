#ifndef MESH_HPP_INCLUDED
#define MESH_HPP_INCLUDED

#include "../common/db_glm.hpp"
#include "../common/global.hpp"
#include <vector>

/*
	������� ����� ��� ���� ( ������������� ����� ) ������.
	�������������� �������: Wavefront OBJ
	todo: milkshape 3d, md2 with anim
*/

namespace demonblade {

	class mesh {

		public:
			mesh( void );
			~mesh( void );
			void operator=( mesh &m );

			// ����� �������� ������ �� �����
			virtual bool load_from_file( std::string file_name ) = 0;

			// ����� ������ ������ � ����
			virtual bool save_to_file( std::string file_name ) = 0;

			// ����� ���������� ��������� �� ��������� � ������������ ������
			std::vector< glm::vec3 >* get_vertex_ptr( void );

			// ����� ���������� ��������� �� ��������� � ����������� ������������
			std::vector< glm::vec2 >* get_texel_ptr( void );

			// ����� ���������� ��������� �� ��������� � ���������
			std::vector< glm::vec3 >* get_normal_ptr( void );

		protected:

			// �������
			std::vector< glm::vec3 > _vertex;

			// ������� ( ���������� ���������� )
			std::vector< glm::vec2 > _texel;

			// �������
			std::vector< glm::vec3 > _normal;

	};	// mesh class

}	// namespace demonblade

#endif // MESH_HPP_INCLUDED
