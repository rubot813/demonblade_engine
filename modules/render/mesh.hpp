#ifndef MESH_HPP_INCLUDED
#define MESH_HPP_INCLUDED

#include "../common/gl_libs.hpp"
#include <sstream>
#include <vector>

/*
	����� ��������� ��� ( ������������� ����� ) ������
	��������� ��������� �������, ���������� ���������� � ����� �������� �� ������
	�������������� �������: Wavefront OBJ
	todo: md2 with anim
*/

namespace demonblade {

	class mesh {

		public:
			// ������ ����������� �� ���������
			mesh( void );

			// ����������� � ��������� ���� �� �����
			// ��������� ����� �������� ����� ����� get_load_result
			mesh( std::string file_name );

			~mesh( void );

			// ������� �����, �� �������� ��� �������� ���
			typedef enum {
				UNKNOWN		= 0,	// ����������� ������
				OBJ					// Wavefront OBJ
			} format_e;

			// ����� �������� ���� �� �����, ���������� ������ �������������
			// � ������ ������ ������ true
			bool load_from_file( std::string file_name );

			// ��������� ������ ����, ��������� ������ �����
			// � ������ ������ ������ true
			bool load_from_file( std::string file_name, format_e format );

			// ����� ���������� ������ �����, �� �������� ��� �������� ���
			format_e get_file_format( void );

			// ����� ���������� ��������� �������� ���� �� �����
			// true - ������� ��������
			bool get_load_result( void );

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
			bool _load_obj( void );

			// ����� ��������� ���������� ����������
			// ��������� ������ �����, ���� ������ ��������, ��� �����
			void _set_internal( format_e fm, bool fl, std::string *fn );

			// ����� ������� ���������� ����������
			void _clean_internal( void );

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

			// ��� �����, �� �������� ��� �������� ���
			std::string				_file_name;

			// ������ �����, �� �������� ��� �������� ���
			format_e				_format;

			// ���� �������� �������� ����
			bool					_succes_flag;
	};	// mesh class

}	// namespace demonblade

#endif // MESH_HPP_INCLUDED
