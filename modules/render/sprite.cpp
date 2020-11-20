#include "sprite.hpp"
#include "../common/db_gl.hpp"

namespace demonblade {
	sprite::sprite( void ) {
		// ���������
		_position	= { .0f, .0f, .0f };
		_scale		= { 1.0f, 1.0f, 1.0f };

		// ����
		_ambient = _diffuse = _specular = { .25f, .25f, .25f, 1.0f };

		// �������
		_texel[ 0 ] = { 0, 0 };
		_texel[ 1 ] = { 0, 1 };
		_texel[ 2 ] = { 1, 1 };
		_texel[ 3 ] = { 1, 1 };
		_texel[ 4 ] = { 1, 0 };
		_texel[ 5 ] = { 0, 0 };

		// ������� �� ���������
		set_size( { 1.0f, 1.0f } );

		// ��� �� ���������
		_type = SPHERICAL;

	}

	sprite::~sprite( void ) {

	}

	// ====

	bool sprite::set_data( type_e type, glm::vec2 size, texture *tex_ptr ) {
		set_type( type );
		set_size( size );
		return set_texture( tex_ptr );
	}

	// ====

	void sprite::set_type( type_e type ) {
		_type = type;
	}

	sprite::type_e sprite::get_type( void ) {
		return _type;
	}

	// ====

	void sprite::set_size( glm::vec2 size ) {
		_size = size;

		_vertex[ 0 ] = {	_size.x,	-_size.y,	0.0f };	// 0
		_vertex[ 1 ] = {	-_size.x,	-_size.y,	0.0f };	// 1
		_vertex[ 2 ] = {	-_size.x,	_size.y,	0.0f };	// 2
		_vertex[ 3 ] = {	-_size.x,	_size.y,	0.0f };	// 2
		_vertex[ 4 ] = {	_size.x,	_size.y,	0.0f };	// 3
		_vertex[ 5 ] = {	_size.x,	-_size.y,	0.0f };	// 1
	}

	glm::vec2 sprite::get_size( void ) {
		return _size;
	}

	// ====

	bool sprite::set_texture( texture *tex_ptr ) {

		bool data_valid = 1;

		if ( tex_ptr && tex_ptr->get_pointer( ) ) {
			_texture = tex_ptr;
			_texture_name = _texture->get_pointer( );
		} else {
			data_valid = 0;
			#ifdef DB_DEBUG
				std::cout << __PRETTY_FUNCTION__ << " -> received texture that not loaded to VRAM";
			#endif // DB_DEBUG
		}

		return data_valid;
	}

	texture* sprite::get_texture( void ) {
		return _texture;
	}

	// ====

	void sprite::render( void ) {
		// ���������� �������� ��������� ������������� ������� modelview � ����
		glPushMatrix( );

		// ��������� ������� ���������: ��������� ����
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ( GLfloat* )&_ambient );

		// ��������� ������� ���������: ��������� ����
		glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, ( GLfloat* )&_diffuse );

		// ��������� ������� ���������: ���������� ����
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, ( GLfloat* )&_specular );

		// ====

		// �������� ������������ ������� ���������
		glTranslatef( _position.x, _position.y, _position.z );

		// ====

		// ��������� �������� ��� ���������
		glBindTexture( GL_TEXTURE_2D, *_texture_name );

		// ��������� ������ ������� �������
		glm::mat4 _matrix_buffer;
		glGetFloatv( GL_MODELVIEW_MATRIX, ( GLfloat* ) &_matrix_buffer );

		_matrix_buffer[ 0 ].x = 1.0f;
		_matrix_buffer[ 0 ].y = 0.0f;
		_matrix_buffer[ 0 ].z = 0.0f;

		// ����������� ������ �� ��������� �� ��� y
		if ( _type == SPHERICAL ) {
			_matrix_buffer[ 1 ].x = 0.0f;
			_matrix_buffer[ 1 ].y = 1.0f;
			_matrix_buffer[ 1 ].z = 0.0f;
		}

		_matrix_buffer[ 2 ].x = 0.0f;
		_matrix_buffer[ 2 ].y = 0.0f;
		_matrix_buffer[ 2 ].z = 1.0f;

		glLoadMatrixf( ( GLfloat* ) &_matrix_buffer );


		// ====

		// ��������� ������ ��������� ��������
		glEnableClientState( GL_VERTEX_ARRAY );

		// ��������� ������ �������� ���������� ���������
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );

		// ��������� ������ �������� ��������
		//glEnableClientState( GL_NORMAL_ARRAY );

		// ====

		// �������� ��������� �� ������ ������
		// ���������� ���������,
		// ��� ������,
		// �������� ������ � �������
		// ��������� �� ������
		glVertexPointer( 3, GL_FLOAT, 0, _vertex );

		// �������� ��������� �� ������ ���������� ���������
		// ���������� ���������,
		// ��� ������,
		// �������� ������ � �������
		// ��������� �� ������
		glTexCoordPointer( 2, GL_FLOAT, 0, _texel );

		// �������� ��������� �� ������ ��������
		// ��� ������,
		// �������� ������ � �������,
		// ��������� �� ������
		//glNormalPointer( GL_FLOAT, 0, _mesh.get_normal_ptr( )->data( ) );

		// ��������� �������
		// ��� ������ ��� ���������
		// ��������� ������ �������
		// ���������� ��������� ��� ���������
		glDrawArrays( GL_TRIANGLES, 0, 6 );

		// ====

		// ���������� ������ �������� ��������
		//glDisableClientState( GL_NORMAL_ARRAY );

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
