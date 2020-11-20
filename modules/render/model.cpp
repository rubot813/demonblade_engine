#include "model.hpp"
#include "../common/db_gl.hpp"

namespace demonblade {
	model::model( void ) {
		// ���������
		_position	= { .0f, .0f, .0f };
		_rotation	= { .0f, .0f, .0f };
		_scale		= { 1.0f, 1.0f, 1.0f };

		// ����
		_ambient = _diffuse = _specular = { .25f, .25f, .25f, 1.0f };

		#ifdef __linux__
		_part.clear( );
		#endif
	}

	model::~model( void ) {
		// no new's, nope
	}

	bool model::add_part( mesh *mesh_ptr, texture *tex_ptr ) {
		bool data_valid = 0;
		_part.push_back( { mesh_ptr, tex_ptr } );
		if ( _part.back( ).is_data_valid( ) )
			data_valid = 1;
		else
			_part.pop_back( );

		return data_valid;
	}

	bool model::remove_part( std::size_t id ) {
		bool flag_removed = 0;
		if ( id < _part.size( ) ) {
			_part.erase( _get_part_iterator( id ) );
			flag_removed = 1;
		}
		#ifdef DB_DEBUG
			else std::cout << __PRETTY_FUNCTION__ << " -> cannot remove model part";
		#endif // DB_DEBUG

		return flag_removed;
	}

	std::size_t model::get_part_count( void ) {
		return _part.size( );
	}

	mesh* model::get_mesh( std::size_t id ) {
		mesh *ptr;
		if ( id < _part.size( ) )
			ptr = _get_part_iterator( id )->get_mesh_ptr( );	// whoa
		else {
			#ifdef DB_DEBUG
				std::cout << __PRETTY_FUNCTION__ << " -> remove nullprt mesh";
			#endif // DB_DEBUG
			ptr = nullptr;
		}
		return ptr;
	}

	texture* model::get_texture( std::size_t id ) {
		texture *ptr;
		if ( id < _part.size( ) )
			ptr = _get_part_iterator( id )->get_texture_ptr( );
		else {
			#ifdef DB_DEBUG
				std::cout << __PRETTY_FUNCTION__ << " -> remove nullprt texture";
			#endif // DB_DEBUG
			ptr = nullptr;
		}
		return ptr;
	}

	std::list< model_part >::iterator model::_get_part_iterator( std::size_t index ) {
		auto iter = _part.begin( );
		std::advance( iter, index );
		return iter;
	}

	// ==== OFFSETS ====
	void model::move( glm::vec3 offset ) {
		_position += offset;
	}
	void model::rotate( glm::vec3 offset ) {
		_rotation += offset;
	}
	void model::scale( glm::vec3 offset ) {
		_scale += offset;
	}
	// ====


	// ==== SETTERS ====
	void model::set_position( glm::vec3 value ) {
		_position = value;
	}
	void model::set_rotation( glm::vec3 value ) {
		_rotation = value;
	}
	void model::set_scale( glm::vec3 value ) {
		_scale = value;
	}
	// ====


	// ==== GETTERS ====
	glm::vec3 model::get_position( void ) {
		return _position;
	}
	glm::vec3 model::get_rotation( void ) {
		return _rotation;
	}
	glm::vec3 model::get_scale( void ) {
		return _scale;
	}
	// ====

	// ==== RENDER ====
	void model::render( void ) {
		// Simplified, check this later
		for ( auto iter : _part )
			_render( &iter );
	}	// render

	void model::render( std::size_t id ) {
		// Simplified, check this later
		_render( &( *_get_part_iterator( id ) ) );
	}

	void model::_render( model_part *part_ptr ) {
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
		glBindTexture( GL_TEXTURE_2D, ( GLuint )( *part_ptr->get_texture_name_ptr( ) ) );

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
		glVertexPointer( 3, GL_FLOAT, 0, part_ptr->get_mesh_ptr( )->get_vertex_ptr( )->data( ) );

		// �������� ��������� �� ������ ���������� ���������
		// ���������� ���������,
		// ��� ������,
		// �������� ������ � �������
		// ��������� �� ������
		glTexCoordPointer( 2, GL_FLOAT, 0, part_ptr->get_mesh_ptr( )->get_texel_ptr( )->data( ) );

		// �������� ��������� �� ������ ��������
		// ��� ������,
		// �������� ������ � �������,
		// ��������� �� ������
		glNormalPointer( GL_FLOAT, 0, part_ptr->get_mesh_ptr( )->get_normal_ptr( )->data( ) );

		// ��������� �������
		// ��� ������ ��� ���������
		// ��������� ������ �������
		// ���������� ��������� ��� ���������
		glDrawArrays( GL_TRIANGLES, 0, part_ptr->get_mesh_ptr( )->get_vertex_ptr( )->size( ) );

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
