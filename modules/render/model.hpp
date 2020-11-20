#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "drawable.hpp"
#include "texture.hpp"
#include "mesh.hpp"

#include <sstream>
#include <list>

/*
	�����, ����������� ������������ �������� � �������� � ���������� ������ ��������.
	������ ������� �� ���� ( ��������� ) � ��������
*/


namespace demonblade {
	// ����� ��������� ���� ������
	class model : public drawable {

		public:
			model( void );
			~model( void );

			// ����� ��������� �������� � ���� ������
			// ��� ������������� ������ ������������� ������������ ���
			// ������ true ���� ��� ��������� � ������� ( ������ � ��������� )
			// ������ false ���� �� ������� ������,
			// ���� ��������� �� �������,
			// ���� ��� �� �������� � RAM,
			// ���� �������� �� ��������� � VRAM
			bool set_data( mesh *mesh_ptr, texture *tex_ptr );

			// ������ ��������� �������� � ���� ������ �� �����������
			bool set_mesh( mesh *mesh_ptr );
			bool set_texture( texture *tex_ptr );

			// ������ ��������� ���������� �� ��� � �������� ������
			mesh*				get_mesh( void );
			texture*			get_texture( void );

			// ����� ��������� ������ ��� �� �����
			void render( void );	// virtual

		private:

			// ��� ������
			mesh				_mesh;

			// �������� � ��� �������� ������
			texture				*_texture;
			texture::texture_t	*_texture_name;

	};	// class model

}	// namespace demonblade

#endif // MODEL_HPP_INCLUDED
