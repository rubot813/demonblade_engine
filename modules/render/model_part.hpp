#ifndef MODEL_PART_HPP_INCLUDED
#define MODEL_PART_HPP_INCLUDED

#include <cstdint>	// C++11
#include "texture.hpp"
#include "mesh.hpp"

/*

	����� ��������� ����� ������, ���������� �� ���� � ��������

	usage:
	db::model_part *mpart;
	mpart = new model_part( ... );
	if ( mpart->is_data_valid( ) ) {
			// ok!
	}

*/

namespace demonblade {

	class model_part {

		public:
			// ����������� � ��������� � ����� ���������� �� ��� � ��������
			model_part( mesh *mesh_ptr, texture *tex_ptr );
			~model_part( void );

			// ����� ������ true, ���� ���������� � ������������ ������ �������
			bool is_data_valid( void );

			// ����� ��������� ��������� �� ���
			mesh* get_mesh_ptr( void );

			// ����� ��������� ��������� ��������� db::texture
			texture* get_texture_ptr( void );

			// ����� ��������� ��������� �� ��� ��������
			texture::texture_t* get_texture_name_ptr( void );

		private:

			// ��������� ����
			mesh		_mesh;

			// ��������� �� ��������� db::texture
			texture		*_texture;

			// ��������� �� ���� name �������� ( VRAM )
			texture::texture_t	*_texture_name;

	};	// class model_part

}	// namespace demonblade
#endif // MODEL_PART_HPP_INCLUDED
