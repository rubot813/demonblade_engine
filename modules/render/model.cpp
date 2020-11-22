#include "model.hpp"
#include "../common/db_gl.hpp"

namespace demonblade {
	model::model( void ) {
		// Положение
		_position	=	_rotation	= { .0f, .0f, .0f };
		_scale		= { 1.0f, 1.0f, 1.0f };

		// Свет
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
		_texture->bind( );
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
		glVertexPointer( 3, GL_FLOAT, 0, _mesh.get_vertex_ptr( )->data( ) );

		// Создание указателя на массив текстурных координат
		// количество координат,
		// тип данных,
		// смещение данных в массиве
		// указатель на массив
		glTexCoordPointer( _texture->get_tex_coords_num( ), GL_FLOAT, 0, _mesh.get_texel_ptr( )->data( ) );

		// Создание указателя на массив нормалей
		// тип данных,
		// смещение данных в массиве,
		// указатель на массив
		glNormalPointer( GL_FLOAT, 0, _mesh.get_normal_ptr( )->data( ) );

		// Отрисовка массива
		// Тип данных для отрисовки
		// начальный индекс массива
		// количество элементов для отрисовки
		glDrawArrays( GL_TRIANGLES, 0, _mesh.get_vertex_ptr( )->size( ) );

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
	}
	// ====

}	// namespace demonblade
