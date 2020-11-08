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

		// Создание объекта текстового файла, открытие файла на чтение
		std::ifstream file;
		file.open( _file_name, std::ios_base::in );

		// Проверка, смогли ли открыть файл
		if ( !file.is_open( ) )
			return 0;

		// Буферы считанной строки и подстроки
		std::string line, buffer;

		// Буфер вершин
		std::vector < glm::vec3 > vertex_buffer;

		// Буфер текселей (текстурных координат)
		std::vector < glm::vec2 > texel_buffer;

		// Буфер нормалей
		std::vector < glm::vec3 > normal_buffer;

		// Буфер поверхностей
		std::vector < _face_ind_s > face_buffer;

		// Считывание построчно, пока есть что читать
		while ( std::getline( file, line ) ) {

			// Подстрока размером 2 символа начиная с нулевого
			buffer = line.substr( 0, 2 );

			// Если объявлена вершина
			if ( buffer == "v " ) {

				// Буфер вершины
				glm::vec3 v_buf;

				// Подстрока начиная со второго символа
				std::stringstream sstream( line.substr( 2 ) );

				// Считывание x, y, z вершины и добавление в буфер
				sstream >> v_buf.x >> v_buf.y >> v_buf.z;
				vertex_buffer.push_back( v_buf );

				continue;
			}

			// Если объявлена текстурная координата
			if ( buffer == "vt" ) {

				// Буфер текселя
				glm::vec2 vt_buf;

				// Подстрока начиная со второго символа
				std::stringstream sstream( line.substr( 2 ) );

				// Считывание x (u), y (v) текселя и добавление в буфер
				sstream >> vt_buf.x >> vt_buf.y;
				texel_buffer.push_back( vt_buf );

				continue;
			}

			// Если объявлена нормаль
			if ( buffer == "vn" ) {

				// Буфер нормали
				glm::vec3 vn_buf;

				// Подстрока начиная со второго символа
				std::stringstream sstream( line.substr( 2 ) );

				// Считывание x, y, z нормали и добавление в буфер
				sstream >> vn_buf.x >> vn_buf.y >> vn_buf.z;
				normal_buffer.push_back( vn_buf );

				continue;
			}

			// Если объявлена поверхность
			if ( buffer == "f " ) {
				// Буфер индексаов поверхности
				_face_ind_s buf;

				// Строковые буферы индекса вершины, текстурной координаты и нормали
				std::string v_buf_str, vt_buf_str, vn_buf_str;

				// Подстрока начиная со второго символа
				std::stringstream sstream( line.substr( 2 ) );

				// Пробег по трем наборам v / vt / vn
				for ( uint8_t i = 0; i < 3; ++i ) {
					// Считывание данных вершины v/vt в строковый буфер до разделителя '/'
					std::getline( sstream, v_buf_str, '/' );
					std::getline( sstream, vt_buf_str, '/' );

					// Считывание данных вершины vn в строковый буфер до разделителя ' '
					std::getline( sstream, vn_buf_str, ' ' );

					// Преобразование строкового значения в числовое
					// TODO: check
					buf.vertex[ i ]	= atoi( v_buf_str.c_str( ) );
					buf.texel[ i ]	= atoi( vt_buf_str.c_str( ) );
					buf.normal[ i ]	= atoi( vn_buf_str.c_str( ) );
				}

				// Занесение индексов в буфер поверхностей
				face_buffer.push_back( buf );

				continue;
			}

			// Если объявлено название модели
			if ( buffer == "o ")
				continue;

			// Если объявлен материал модели ( mtllib )
			if ( buffer == "mt" )
				continue;

			// Если объявлен комментарий
			if ( buffer[ 0 ] == '#' )
				continue;

			// Если изменена настройка шейдинга
			if ( buffer[ 0 ] == 's' )
				continue;

			// Если определение неизвестно
			// TODO: можно хотя бы строчку вывести, где не смогли прочитать
			return 0;

		} // Конец прохода по файлу

		// Проход по элементам буфера поверхностей
		std::vector < _face_ind_s >::iterator iter = face_buffer.begin( );
		while ( iter != face_buffer.end( ) ) {
			// Добавление вершин полигона
			_vertex.push_back( { vertex_buffer[ ( *iter ).vertex.x - 1 ].x, vertex_buffer[ ( *iter ).vertex.x - 1 ].y, vertex_buffer[ ( *iter ).vertex.x - 1 ].z } );
			_vertex.push_back( { vertex_buffer[ ( *iter ).vertex.y - 1 ].x, vertex_buffer[ ( *iter ).vertex.y - 1 ].y, vertex_buffer[ ( *iter ).vertex.y - 1 ].z } );
			_vertex.push_back( { vertex_buffer[ ( *iter ).vertex.z - 1 ].x, vertex_buffer[ ( *iter ).vertex.z - 1 ].y, vertex_buffer[ ( *iter ).vertex.z - 1 ].z } );

			// Добавление текстурных координат полигона
			_texel.push_back( { texel_buffer[ ( *iter ).texel.x - 1 ].x, texel_buffer[ ( *iter ).texel.x - 1 ].y } );
			_texel.push_back( { texel_buffer[ ( *iter ).texel.y - 1 ].x, texel_buffer[ ( *iter ).texel.y - 1 ].y } );
			_texel.push_back( { texel_buffer[ ( *iter ).texel.z - 1 ].x, texel_buffer[ ( *iter ).texel.z - 1 ].y } );

			// Добавление нормалей полигона
			_normal.push_back( { normal_buffer[ ( *iter ).normal.x - 1 ].x, normal_buffer[ ( *iter ).normal.x - 1 ].y, normal_buffer[ ( *iter ).normal.x - 1 ].z } );
			_normal.push_back( { normal_buffer[ ( *iter ).normal.y - 1 ].x, normal_buffer[ ( *iter ).normal.y - 1 ].y, normal_buffer[ ( *iter ).normal.y - 1 ].z } );
			_normal.push_back( { normal_buffer[ ( *iter ).normal.z - 1 ].x, normal_buffer[ ( *iter ).normal.z - 1 ].y, normal_buffer[ ( *iter ).normal.z - 1 ].z } );

			++iter;
		}

		return 1;
	}	// _load_obj
}	// namespace demonblade
