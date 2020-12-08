#ifndef OBJ_HPP_INCLUDED
#define OBJ_HPP_INCLUDED

#include "../render/mesh.hpp"

#include <sstream>
#include <fstream>

/*
	����� ��������� �������� � �������� ������� OBJ Wavefront
	������� �� ������ mesh
*/

namespace demonblade {

	class obj : public mesh {

		public:
			obj( void );
			~obj( void );

			// ����� �������� ������ �� �����
			bool load_from_file( std::string file_name );

			// ����� ������ ������ � ����
			bool save_to_file( std::string file_name );

		private:

			// ��������� �������� ������ ��������
			typedef struct {
				glm::uvec3 vertex;
				glm::uvec3 texel;
				glm::uvec3 normal;
			} _polygon_index_s;

	};	// obj class

}	// namespace demonblade

#endif // OBJ_HPP_INCLUDED
