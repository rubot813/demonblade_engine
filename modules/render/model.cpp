#include "model.hpp"
#include "../common/gl_libs.hpp"

namespace demonblade {
	model::model( void ) {
		_scale = { 1.0f, 1.0f, 1.0f };
		_ambient = _diffuse = _specular = { .25f, .25f, .25f, 1.0f };
	}

	// Метод загрузки массивов вершин, текселей и нормалей из Wavefront OBJ файла
	// Вернет true в случае успеха
	bool model::load_from_obj( std::string file_name ) {

		// Создание объекта текстового файла, открытие файла на чтение
		std::ifstream file;
		file.open( file_name, std::ios_base::in );

		// Проверка, что файл открыт
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
	}	// load_from_obj

	// Метод установки текстуры для модели
	// Вернет true в случае успеха
	bool model::set_texture( texture::texture_t *tex ) {
		_texture = tex;
		return _texture != nullptr;
	}

	// Методы перемещения, вращения и масштабирования модели
	inline void model::move( glm::vec3 offset ) {
		_position += offset;
	}
	inline void model::rotate( glm::vec3 offset ) {
		_rotation += offset;
	}
	inline void model::scale( glm::vec3 offset ) {
		_scale += offset;
	}

	// Методы установки позиции, поворота и масштаба модели
	inline void model::set_position( glm::vec3 value ) {
		_position = value;
	}
	inline void model::set_rotation( glm::vec3 value ) {
		_rotation = value;
	}
	inline void model::set_scale( glm::vec3 value ) {
		_scale = value;
	}

	// Метод отрисовки модели
	void model::render( void ) {

		// Сохранение текущего состояния трансформации матрицы modelview в стек
		glPushMatrix( );

		// Установка свойств материала: рассеяный свет
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ( GLfloat* )&_ambient );

		// Установка свойств материала: диффузный свет
		glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, ( GLfloat* )&_diffuse );

		// Установка свойств материала: отраженный свет
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, ( GLfloat* )&_specular );

		// ====

		// Смещение модели относительно нулевых координат
		glTranslatef( _position.x, _position.y, _position.z );

		// Вращение системы координат относительно модели
		// По оси x
		glRotatef( _rotation.x, 1.0f, 0.0f, 0.0f );

		// По оси y
		glRotatef( _rotation.y, 0.0f, 1.0f, 0.0f );

		// По оси z
		glRotatef( _rotation.z, 0.0f, 0.0f, 1.0f );

		// Масштабирование модели
		glScalef( _scale.x, _scale.y, _scale.z );

		// ====

		// Установка текстуры для отрисовки
		glBindTexture( GL_TEXTURE_2D, *_texture );

		// ====

		// Включение режима вершинных массивов
		glEnableClientState( GL_VERTEX_ARRAY );

		// Включение режима массивов текстурных координат
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );

		// Включение режима массивов нормалей
		glEnableClientState( GL_NORMAL_ARRAY );

		// ====

		// Создание указателя на массив вершин
		// количество координат,
		// тип данных,
		// смещение данных в массиве
		// указатель на массив
		glVertexPointer( 3, GL_FLOAT, 0, _vertex.data( ) );

		// Создание указателя на массив текстурных координат
		// количество координат,
		// тип данных,
		// смещение данных в массиве
		// указатель на массив
		glTexCoordPointer( 2, GL_FLOAT, 0, _texel.data( ) );

		// Создание указателя на массив нормалей
		// тип данных,
		// смещение данных в массиве,
		// указатель на массив
		glNormalPointer( GL_FLOAT, 0, _normal.data( ) );

		// Отрисовка массива
		// Тип данных для отрисовки
		// начальный индекс массива
		// количество элементов для отрисовки
		glDrawArrays( GL_TRIANGLES, 0, _vertex.size( ) );

		// ====

		// Выключение режима массивов нормалей
		glDisableClientState( GL_NORMAL_ARRAY );

		// Выключение режима массивов текстурных координат
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );

		// Выключение режима вершинных массивов
		glDisableClientState( GL_VERTEX_ARRAY );

		// ====

		// Восстановление состояния матрицы modelview из стека
		glPopMatrix( );
	}	// render

}	// namespace demonblade
