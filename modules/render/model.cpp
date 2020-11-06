#include "model.hpp"
#include "../common/gl_libs.hpp"

namespace demonblade {
	model::model( void ) {
		_scale = { 1.0f, 1.0f, 1.0f };
		_ambient = _diffuse = _specular = { .25f, .25f, .25f, 1.0f };
	}

	// ����� �������� �������� ������, �������� � �������� �� Wavefront OBJ �����
	// ������ true � ������ ������
	bool model::load_from_obj( std::string file_name ) {

		// �������� ������� ���������� �����, �������� ����� �� ������
		std::ifstream file;
		file.open( file_name, std::ios_base::in );

		// ��������, ��� ���� ������
		if ( !file.is_open( ) )
			return 0;

		// ������ ��������� ������ � ���������
		std::string line, buffer;

		// ����� ������
		std::vector < glm::vec3 > vertex_buffer;

		// ����� �������� (���������� ���������)
		std::vector < glm::vec2 > texel_buffer;

		// ����� ��������
		std::vector < glm::vec3 > normal_buffer;

		// ����� ������������
		std::vector < _face_ind_s > face_buffer;

		// ���������� ���������, ���� ���� ��� ������
		while ( std::getline( file, line ) ) {

			// ��������� �������� 2 ������� ������� � ��������
			buffer = line.substr( 0, 2 );

			// ���� ��������� �������
			if ( buffer == "v " ) {

				// ����� �������
				glm::vec3 v_buf;

				// ��������� ������� �� ������� �������
				std::stringstream sstream( line.substr( 2 ) );

				// ���������� x, y, z ������� � ���������� � �����
				sstream >> v_buf.x >> v_buf.y >> v_buf.z;
				vertex_buffer.push_back( v_buf );

				continue;
			}

			// ���� ��������� ���������� ����������
			if ( buffer == "vt" ) {

				// ����� �������
				glm::vec2 vt_buf;

				// ��������� ������� �� ������� �������
				std::stringstream sstream( line.substr( 2 ) );

				// ���������� x (u), y (v) ������� � ���������� � �����
				sstream >> vt_buf.x >> vt_buf.y;
				texel_buffer.push_back( vt_buf );

				continue;
			}

			// ���� ��������� �������
			if ( buffer == "vn" ) {

				// ����� �������
				glm::vec3 vn_buf;

				// ��������� ������� �� ������� �������
				std::stringstream sstream( line.substr( 2 ) );

				// ���������� x, y, z ������� � ���������� � �����
				sstream >> vn_buf.x >> vn_buf.y >> vn_buf.z;
				normal_buffer.push_back( vn_buf );

				continue;
			}

			// ���� ��������� �����������
			if ( buffer == "f " ) {
				// ����� ��������� �����������
				_face_ind_s buf;

				// ��������� ������ ������� �������, ���������� ���������� � �������
				std::string v_buf_str, vt_buf_str, vn_buf_str;

				// ��������� ������� �� ������� �������
				std::stringstream sstream( line.substr( 2 ) );

				// ������ �� ���� ������� v / vt / vn
				for ( uint8_t i = 0; i < 3; ++i ) {
					// ���������� ������ ������� v/vt � ��������� ����� �� ����������� '/'
					std::getline( sstream, v_buf_str, '/' );
					std::getline( sstream, vt_buf_str, '/' );

					// ���������� ������ ������� vn � ��������� ����� �� ����������� ' '
					std::getline( sstream, vn_buf_str, ' ' );

					// �������������� ���������� �������� � ��������
					// TODO: check
					buf.vertex[ i ]	= atoi( v_buf_str.c_str( ) );
					buf.texel[ i ]	= atoi( vt_buf_str.c_str( ) );
					buf.normal[ i ]	= atoi( vn_buf_str.c_str( ) );
				}

				// ��������� �������� � ����� ������������
				face_buffer.push_back( buf );

				continue;
			}

			// ���� ��������� �������� ������
			if ( buffer == "o ")
				continue;

			// ���� �������� �������� ������ ( mtllib )
			if ( buffer == "mt" )
				continue;

			// ���� �������� �����������
			if ( buffer[ 0 ] == '#' )
				continue;

			// ���� �������� ��������� ��������
			if ( buffer[ 0 ] == 's' )
				continue;

			// ���� ����������� ����������
			// TODO: ����� ���� �� ������� �������, ��� �� ������ ���������
			return 0;

		} // ����� ������� �� �����

		// ������ �� ��������� ������ ������������
		std::vector < _face_ind_s >::iterator iter = face_buffer.begin( );
		while ( iter != face_buffer.end( ) ) {
			// ���������� ������ ��������
			_vertex.push_back( { vertex_buffer[ ( *iter ).vertex.x - 1 ].x, vertex_buffer[ ( *iter ).vertex.x - 1 ].y, vertex_buffer[ ( *iter ).vertex.x - 1 ].z } );
			_vertex.push_back( { vertex_buffer[ ( *iter ).vertex.y - 1 ].x, vertex_buffer[ ( *iter ).vertex.y - 1 ].y, vertex_buffer[ ( *iter ).vertex.y - 1 ].z } );
			_vertex.push_back( { vertex_buffer[ ( *iter ).vertex.z - 1 ].x, vertex_buffer[ ( *iter ).vertex.z - 1 ].y, vertex_buffer[ ( *iter ).vertex.z - 1 ].z } );

			// ���������� ���������� ��������� ��������
			_texel.push_back( { texel_buffer[ ( *iter ).texel.x - 1 ].x, texel_buffer[ ( *iter ).texel.x - 1 ].y } );
			_texel.push_back( { texel_buffer[ ( *iter ).texel.y - 1 ].x, texel_buffer[ ( *iter ).texel.y - 1 ].y } );
			_texel.push_back( { texel_buffer[ ( *iter ).texel.z - 1 ].x, texel_buffer[ ( *iter ).texel.z - 1 ].y } );

			// ���������� �������� ��������
			_normal.push_back( { normal_buffer[ ( *iter ).normal.x - 1 ].x, normal_buffer[ ( *iter ).normal.x - 1 ].y, normal_buffer[ ( *iter ).normal.x - 1 ].z } );
			_normal.push_back( { normal_buffer[ ( *iter ).normal.y - 1 ].x, normal_buffer[ ( *iter ).normal.y - 1 ].y, normal_buffer[ ( *iter ).normal.y - 1 ].z } );
			_normal.push_back( { normal_buffer[ ( *iter ).normal.z - 1 ].x, normal_buffer[ ( *iter ).normal.z - 1 ].y, normal_buffer[ ( *iter ).normal.z - 1 ].z } );

			++iter;
		}

		return 1;
	}	// load_from_obj

	// ����� ��������� �������� ��� ������
	// ������ true � ������ ������
	bool model::set_texture( texture::texture_t *tex ) {
		_texture = tex;
		return _texture != nullptr;
	}

	// ������ �����������, �������� � ��������������� ������
	inline void model::move( glm::vec3 offset ) {
		_position += offset;
	}
	inline void model::rotate( glm::vec3 offset ) {
		_rotation += offset;
	}
	inline void model::scale( glm::vec3 offset ) {
		_scale += offset;
	}

	// ������ ��������� �������, �������� � �������� ������
	inline void model::set_position( glm::vec3 value ) {
		_position = value;
	}
	inline void model::set_rotation( glm::vec3 value ) {
		_rotation = value;
	}
	inline void model::set_scale( glm::vec3 value ) {
		_scale = value;
	}

	// ����� ��������� ������
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
		glBindTexture( GL_TEXTURE_2D, *_texture );

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
		glVertexPointer( 3, GL_FLOAT, 0, _vertex.data( ) );

		// �������� ��������� �� ������ ���������� ���������
		// ���������� ���������,
		// ��� ������,
		// �������� ������ � �������
		// ��������� �� ������
		glTexCoordPointer( 2, GL_FLOAT, 0, _texel.data( ) );

		// �������� ��������� �� ������ ��������
		// ��� ������,
		// �������� ������ � �������,
		// ��������� �� ������
		glNormalPointer( GL_FLOAT, 0, _normal.data( ) );

		// ��������� �������
		// ��� ������ ��� ���������
		// ��������� ������ �������
		// ���������� ��������� ��� ���������
		glDrawArrays( GL_TRIANGLES, 0, _vertex.size( ) );

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
