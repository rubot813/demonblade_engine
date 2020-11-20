#include "sprite.hpp"
#include "../common/db_gl.hpp"

namespace demonblade {
	sprite::sprite( void ) {
		// Положение
		_position	= { .0f, .0f, .0f };
		_scale		= { 1.0f, 1.0f, 1.0f };

		// Свет
		_ambient = _diffuse = _specular = { .25f, .25f, .25f, 1.0f };

		// Тексели
		_texel[ 0 ] = { 0, 0 };
		_texel[ 1 ] = { 0, 1 };
		_texel[ 2 ] = { 1, 1 };
		_texel[ 3 ] = { 1, 1 };
		_texel[ 4 ] = { 1, 0 };
		_texel[ 5 ] = { 0, 0 };

		// Размеры по умолчанию
		set_size( { 1.0f, 1.0f } );

		// Тип по умолчанию
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
		// Сохранение текущего состояния трансформации матрицы modelview в стек
		glPushMatrix( );

		// Установка свойств материала: рассеяный свет
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ( GLfloat* )&_ambient );

		// Установка свойств материала: диффузный свет
		glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, ( GLfloat* )&_diffuse );

		// Установка свойств материала: отраженный свет
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, ( GLfloat* )&_specular );

		// ====

		// Смещение относительно нулевых координат
		glTranslatef( _position.x, _position.y, _position.z );

		// ====

		// Установка текстуры для отрисовки
		glBindTexture( GL_TEXTURE_2D, *_texture_name );

		// Получение буфера видовой матрицы
		glm::mat4 _matrix_buffer;
		glGetFloatv( GL_MODELVIEW_MATRIX, ( GLfloat* ) &_matrix_buffer );

		_matrix_buffer[ 0 ].x = 1.0f;
		_matrix_buffer[ 0 ].y = 0.0f;
		_matrix_buffer[ 0 ].z = 0.0f;

		// Сферический спрайт не вращается по оси y
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

		// Включение режима вершинных массивов
		glEnableClientState( GL_VERTEX_ARRAY );

		// Включение режима массивов текстурных координат
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );

		// Включение режима массивов нормалей
		//glEnableClientState( GL_NORMAL_ARRAY );

		// ====

		// Создание указателя на массив вершин
		// количество координат,
		// тип данных,
		// смещение данных в массиве
		// указатель на массив
		glVertexPointer( 3, GL_FLOAT, 0, _vertex );

		// Создание указателя на массив текстурных координат
		// количество координат,
		// тип данных,
		// смещение данных в массиве
		// указатель на массив
		glTexCoordPointer( 2, GL_FLOAT, 0, _texel );

		// Создание указателя на массив нормалей
		// тип данных,
		// смещение данных в массиве,
		// указатель на массив
		//glNormalPointer( GL_FLOAT, 0, _mesh.get_normal_ptr( )->data( ) );

		// Отрисовка массива
		// Тип данных для отрисовки
		// начальный индекс массива
		// количество элементов для отрисовки
		glDrawArrays( GL_TRIANGLES, 0, 6 );

		// ====

		// Выключение режима массивов нормалей
		//glDisableClientState( GL_NORMAL_ARRAY );

		// Выключение режима массивов текстурных координат
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );

		// Выключение режима вершинных массивов
		glDisableClientState( GL_VERTEX_ARRAY );

		// ====

		// Восстановление состояния матрицы modelview из стека
		glPopMatrix( );
	}
	// ====

}	// namespace demonblade
