#include "mesh.hpp"
#include <fstream>

namespace demonblade {

	mesh::mesh( void ) {
		_clean_internal( );
	}

	mesh::mesh( std::string file_name ) {
		load_from_file( file_name );
	}

	mesh::~mesh( void ) {

	}

	bool mesh::load_from_file( std::string file_name ) {
		return load_from_file( file_name, _get_extension( &file_name ) );
	}

	bool mesh::load_from_file( std::string file_name, format_e format ) {
		_clean_internal( );

		switch ( format ) {
			case UNKNOWN:
				break;
			case OBJ: {
				if ( _load_obj( ) )
					_set_internal( OBJ, 1, &file_name );
				break;
			}
			default:
				break;
		}
		return _succes_flag;
	}

	mesh::format_e mesh::_get_extension( std::string *path ) {
		std::size_t dot_index = path->rfind( '.' );
		if ( dot_index == std::string::npos )
			return UNKNOWN;
		std::string ext = path->substr( dot_index + 1 );
		if ( ext == "obj" || ext == "OBJ" )
			return OBJ;
		return UNKNOWN;
	}

	mesh::format_e mesh::get_file_format( void ) {
		return _format;
	}

	bool mesh::get_load_result( void ) {
		return _succes_flag;
	}

	void mesh::_set_internal( mesh::format_e fm, bool fl, std::string *fn ) {
		_format			= fm;
		_succes_flag	= fl;
		_file_name		= *fn;
	}

	void mesh::_clean_internal( void ) {
		_format			= UNKNOWN;
		_succes_flag	= 0;
		_file_name.clear( );
	}

	std::vector< glm::vec3 >* mesh::get_vertex_ptr( void ) {
		return &_vertex;
	}

	std::vector< glm::vec2 >* mesh::get_texel_ptr( void ) {
		return &_texel;
	}

	std::vector< glm::vec3 >* mesh::get_normal_ptr( void ) {
		return &_normal;
	}

	bool mesh::_load_obj( void ) {

		// �������� ������� ���������� �����, �������� ����� �� ������
		std::ifstream file;
		file.open( _file_name, std::ios_base::in );

		// ��������, ������ �� ������� ����
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
	}	// _load_obj
}	// namespace demonblade
