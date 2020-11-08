#include "model.hpp"
#include <iostream>

namespace demonblade {
	model::model( void ) {
		_scale = { 1.0f, 1.0f, 1.0f };
		_ambient = _diffuse = _specular = { .25f, .25f, .25f, 1.0f };

		// �������� ������ ��� �������� � ���
		_mesh = new mesh( );
		_texture = new texture( );

		// ������ �����, ��� �������� ������ ��� �������� � ���
		_mesh_allocated = 1;
		_tex_allocated = 1;
	}

	model::model( mesh *m, texture *tex ) {
		std::cout << "HERE";
		_mesh = m;
		_texture = tex;
		_texture_vram = _texture->get_pointer( );
		std::cout << "HERE2";
		// �����, ��� ������ �� ��������
		_mesh_allocated = 0;
		_tex_allocated = 0;
	}

	model::model( mesh msh, texture tex ) {

		_mesh = &msh;
		_texture = &tex;
		_texture_vram = _texture->get_pointer( );

		// �����, ��� ������ �� ��������
		_mesh_allocated = 0;
		_tex_allocated = 0;
	}

	model::~model( void ) {
		// ���� �������� ������ ��� �������� � ���,
		// �� ����� ��� �����������
		if ( _mesh_allocated )
			delete _mesh;
		if ( _tex_allocated )
			delete _texture;
	}

	bool model::set_texture( texture *tex ) {
		// ���������� ������, ���� ��� ���� �������� ��� ������� ��������
		if ( _tex_allocated ) {
			delete _texture;
			_tex_allocated = 0;
		}

		// ��������� ����� ��������
		if ( tex ) {
			_texture = tex;
			_texture_vram = _texture->get_pointer( );
		}
		return ( _texture != nullptr &&
				_texture_vram != nullptr );
	}

	bool model::set_mesh( mesh *msh ) {
		// ���������� ������, ���� ��� ���� �������� ��� ������� ���
		if ( _mesh_allocated ) {
			delete _mesh;
			_mesh_allocated = 0;
		}

		// ��������� ������ ����
		_mesh = msh;
		return ( _mesh != nullptr );
	}

	texture* model::get_texture( void ) {
		return _texture;
	}

	mesh* model::get_mesh( void ) {
		return _mesh;
	}

	void model::move( glm::vec3 offset ) {
		_position += offset;
	}
	void model::rotate( glm::vec3 offset ) {
		_rotation += offset;
	}
	void model::scale( glm::vec3 offset ) {
		_scale += offset;
	}

	void model::set_position( glm::vec3 value ) {
		_position = value;
	}
	void model::set_rotation( glm::vec3 value ) {
		_rotation = value;
	}
	void model::set_scale( glm::vec3 value ) {
		_scale = value;
	}

	glm::vec3 model::get_position( void ) {
		return _position;
	}
	glm::vec3 model::get_rotation( void ) {
		return _rotation;
	}
	glm::vec3 model::get_scale( void ) {
		return _scale;
	}

	void model::render( void ) {

		// ���������� �������� ��������� ������������� ������� modelview � ����
		glPushMatrix( );

		// ��������� ������� ���������: ��������� ����
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ( GLfloat* )&_ambient );

		// ��������� ������� ���������: ��������� ����
		glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, ( GLfloat* )&_diffuse );

		// ��������� ������� ���������: ���������� ����
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, ( GLfloat* )&_specular );

		// ====

		// �������� ������ ������������ ������� ���������
		glTranslatef( _position.x, _position.y, _position.z );

		// �������� ������� ��������� ������������ ������
		// �� ��� x
		glRotatef( _rotation.x, 1.0f, 0.0f, 0.0f );

		// �� ��� y
		glRotatef( _rotation.y, 0.0f, 1.0f, 0.0f );

		// �� ��� z
		glRotatef( _rotation.z, 0.0f, 0.0f, 1.0f );

		// ��������������� ������
		glScalef( _scale.x, _scale.y, _scale.z );

		// ====

		// ��������� �������� ��� ���������
		glBindTexture( GL_TEXTURE_2D, *_texture_vram );

		// ====

		// ��������� ������ ��������� ��������
		glEnableClientState( GL_VERTEX_ARRAY );

		// ��������� ������ �������� ���������� ���������
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );

		// ��������� ������ �������� ��������
		glEnableClientState( GL_NORMAL_ARRAY );

		// ====

		// �������� ��������� �� ������ ������
		// ���������� ���������,
		// ��� ������,
		// �������� ������ � �������
		// ��������� �� ������
		glVertexPointer( 3, GL_FLOAT, 0, _mesh->get_vertex_ptr( ) );

		// �������� ��������� �� ������ ���������� ���������
		// ���������� ���������,
		// ��� ������,
		// �������� ������ � �������
		// ��������� �� ������
		glTexCoordPointer( 2, GL_FLOAT, 0, _mesh->get_texel_ptr( ) );

		// �������� ��������� �� ������ ��������
		// ��� ������,
		// �������� ������ � �������,
		// ��������� �� ������
		glNormalPointer( GL_FLOAT, 0, _mesh->get_normal_ptr( ) );

		// ��������� �������
		// ��� ������ ��� ���������
		// ��������� ������ �������
		// ���������� ��������� ��� ���������
		glDrawArrays( GL_TRIANGLES, 0, _mesh->get_vertex_ptr( )->size( ) );

		// ====

		// ���������� ������ �������� ��������
		glDisableClientState( GL_NORMAL_ARRAY );

		// ���������� ������ �������� ���������� ���������
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );

		// ���������� ������ ��������� ��������
		glDisableClientState( GL_VERTEX_ARRAY );

		// ====

		// �������������� ��������� ������� modelview �� �����
		glPopMatrix( );
	}	// render

}	// namespace demonblade
