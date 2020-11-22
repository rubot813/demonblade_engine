#include "model.hpp"
#include "../common/db_gl.hpp"

namespace demonblade {
	model::model( void ) {
		// ���������
		_position	=	_rotation	= { .0f, .0f, .0f };
		_scale		= { 1.0f, 1.0f, 1.0f };

		// ����
		_ambient = _diffuse = _specular = { .25f, .25f, .25f, 1.0f };
	}

	model::~model( void ) {

	}

	bool model::set_data( mesh *mesh_ptr, texture *tex_ptr ) {
		return ( set_mesh( mesh_ptr ) && set_texture( tex_ptr ) );
	}

	bool model::set_mesh( mesh *mesh_ptr ) {

		bool data_valid = 1;

		if ( mesh_ptr )
			_mesh = *mesh_ptr;
		else {
			data_valid = 0;
			#ifdef DB_DEBUG
			debug::get_instance( )->warn( std::string( __FUNCTION__ ) + " -> received null mesh pointer\n" );
			#endif // DB_DEBUG
		}

		return data_valid;
	}

	bool model::set_texture( texture *tex_ptr ) {

		bool data_valid = 1;

		if ( tex_ptr && tex_ptr->get_pointer( ) ) {
			_texture = tex_ptr;
		} else {
			data_valid = 0;
			#ifdef DB_DEBUG
			debug::get_instance( )->warn( std::string( __FUNCTION__ ) + " -> received texture that not loaded to VRAM\n" );
			#endif // DB_DEBUG
		}

		return data_valid;
	}

	mesh* model::get_mesh( void ) {
		return &_mesh;
	}

	texture* model::get_texture( void ) {
		return _texture;
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
		_texture->bind( );
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
		glVertexPointer( 3, GL_FLOAT, 0, _mesh.get_vertex_ptr( )->data( ) );

		// �������� ��������� �� ������ ���������� ���������
		// ���������� ���������,
		// ��� ������,
		// �������� ������ � �������
		// ��������� �� ������
		glTexCoordPointer( _texture->get_tex_coords_num( ), GL_FLOAT, 0, _mesh.get_texel_ptr( )->data( ) );

		// �������� ��������� �� ������ ��������
		// ��� ������,
		// �������� ������ � �������,
		// ��������� �� ������
		glNormalPointer( GL_FLOAT, 0, _mesh.get_normal_ptr( )->data( ) );

		// ��������� �������
		// ��� ������ ��� ���������
		// ��������� ������ �������
		// ���������� ��������� ��� ���������
		glDrawArrays( GL_TRIANGLES, 0, _mesh.get_vertex_ptr( )->size( ) );

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
	}
	// ====

}	// namespace demonblade
