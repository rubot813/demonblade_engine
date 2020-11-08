#include "model.hpp"
#include <iostream>

namespace demonblade {
	model::model( void ) {
		_scale = { 1.0f, 1.0f, 1.0f };
		_ambient = _diffuse = _specular = { .25f, .25f, .25f, 1.0f };

		// Выделяем память под текстуру и меш
		_mesh = new mesh( );
		_texture = new texture( );

		// Ставим флаги, что выделили память под текстуру и меш
		_mesh_allocated = 1;
		_tex_allocated = 1;
	}

	model::model( mesh *m, texture *tex ) {
		std::cout << "HERE";
		_mesh = m;
		_texture = tex;
		_texture_vram = _texture->get_pointer( );
		std::cout << "HERE2";
		// Флаги, что память не выделяли
		_mesh_allocated = 0;
		_tex_allocated = 0;
	}

	model::model( mesh msh, texture tex ) {

		_mesh = &msh;
		_texture = &tex;
		_texture_vram = _texture->get_pointer( );

		// Флаги, что память не выделяли
		_mesh_allocated = 0;
		_tex_allocated = 0;
	}

	model::~model( void ) {
		// Если выделяли память под текстуру и меш,
		// то здесь она освободится
		if ( _mesh_allocated )
			delete _mesh;
		if ( _tex_allocated )
			delete _texture;
	}

	bool model::set_texture( texture *tex ) {
		// Освобождаю память, если она была выделена под текущую текстуру
		if ( _tex_allocated ) {
			delete _texture;
			_tex_allocated = 0;
		}

		// Установка новой текстуры
		if ( tex ) {
			_texture = tex;
			_texture_vram = _texture->get_pointer( );
		}
		return ( _texture != nullptr &&
				_texture_vram != nullptr );
	}

	bool model::set_mesh( mesh *msh ) {
		// Освобождаю память, если она была выделена под текущий меш
		if ( _mesh_allocated ) {
			delete _mesh;
			_mesh_allocated = 0;
		}

		// Установка нового меша
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
		glBindTexture( GL_TEXTURE_2D, *_texture_vram );

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
		glVertexPointer( 3, GL_FLOAT, 0, _mesh->get_vertex_ptr( ) );

		// Создание указателя на массив текстурных координат
		// количество координат,
		// тип данных,
		// смещение данных в массиве
		// указатель на массив
		glTexCoordPointer( 2, GL_FLOAT, 0, _mesh->get_texel_ptr( ) );

		// Создание указателя на массив нормалей
		// тип данных,
		// смещение данных в массиве,
		// указатель на массив
		glNormalPointer( GL_FLOAT, 0, _mesh->get_normal_ptr( ) );

		// Отрисовка массива
		// Тип данных для отрисовки
		// начальный индекс массива
		// количество элементов для отрисовки
		glDrawArrays( GL_TRIANGLES, 0, _mesh->get_vertex_ptr( )->size( ) );

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
