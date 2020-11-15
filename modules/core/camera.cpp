#include "camera.hpp"
#include <iostream>

namespace demonblade {
	camera::camera( void ) {
		_up = { .0, 1.0f, .0f };
	}

	camera::camera( uint16_t width, uint16_t height, float fov, float z_near, float z_far ) {
		_up = { .0, 1.0f, .0f };
		set_viewport( width, height, fov, z_near, z_far );
	}

	camera::~camera( void ) {

	}

	void camera::set_viewport( uint16_t width, uint16_t height, float fov, float z_near, float z_far ) {
		// Сохранение параметров
		_viewport_width		= width;
		_viewport_height	= height;
		_fov				= fov;
		_z_near				= z_near;
		_z_far				= z_far;

		// Установка матрицы проекции
		_set_projection_matrix( );

	}

	void camera::_set_projection_matrix( void ) {
		// Установка положения и размера порта вывода
		glViewport( 0, 0, _viewport_width, _viewport_height );

		// Выбор матрицы проекции
		glMatrixMode( GL_PROJECTION );

		// Обнуление матрицы проекции
		glLoadIdentity( );

		// Расчет соотношения сторон экрана
		float aspect_ratio = ( ( float )_viewport_width / ( float )_viewport_height );

		// Определение матрицы наблюдения перспективной проекции ( GL_PROJECTION ):
		// Угол обзора по оси Y
		// Соотношение сторон экрана
		// Ближняя плоскость усеченной пирамиды наблюдения
		// Дальняя плоскость усеченной пирамиды наблюдения
		glm::mat4 projection_mat = glm::perspective( glm::radians( _fov ), aspect_ratio, _z_near, _z_far );
		glLoadMatrixf( glm::value_ptr( projection_mat ) );

		// Выбор матрицы наблюдения моделей
		glMatrixMode( GL_MODELVIEW );

		// Обнуление матрицы
		glLoadIdentity( );
	}

	void camera::project( void ) {

		// Обнуление матрицы MODELVIEW
		glLoadIdentity( );

		// Считаем матрицу MODELVIEW и устанавливаем трансформацию относительно камеры
		glm::mat4 lookat_mat = glm::lookAt( _position, _center, _up );
		glLoadMatrixf( glm::value_ptr( lookat_mat ) );
	}

	void camera::set_position( glm::vec3 value ) {
		_position = value;
	}

	void camera::set_center( glm::vec3 value ) {
		_center = value;
	}

	void camera::set_up( glm::vec3 value ) {
		_up = value;
	}

	glm::vec3 camera::get_position( void  ) {
		return _position;
	}

	glm::vec3 camera::get_center( void  ) {
		return _center;
	}

	glm::vec3 camera::get_up( void ) {
		return _up;
	}
}	// namespace demonblade
