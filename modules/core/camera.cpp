#include "camera.hpp"

namespace demonblade {
	camera::camera( void ) {
		// Инициализация векторов
		_position	= { .0f, .0f, .0f };
		_center		= { .0f, .0f, .0f };
		_up			= { .0, 1.0f, .0f };
	}

	camera::~camera( void ) {

	}

	void camera::set_viewport( uint16_t width, uint16_t height, float fov, float z_near, float z_far ) {
		// Установка положения и размера порта вывода
		glViewport( 0, 0, width, height );

		// Выбор матрицы проекции
		glMatrixMode( GL_PROJECTION );

		// Обнуление матрицы проекции
		glLoadIdentity( );

		// Расчет соотношения сторон экрана
		float aspect_ratio = ( ( float )width / ( float )height );

		// Определение матрицы наблюдения перспективной проекции ( GL_PROJECTION ):
		// Угол обзора по оси Y
		// Соотношение сторон экрана
		// Ближняя плоскость усеченной пирамиды наблюдения
		// Дальняя плоскость усеченной пирамиды наблюдения
		glm::mat4 projection_mat = glm::perspective( glm::radians( fov ), aspect_ratio, z_near, z_far );
		glLoadMatrixf( glm::value_ptr( projection_mat ) );

		// Выбор матрицы наблюдения моделей
		glMatrixMode( GL_MODELVIEW );

		// Обнуление матрицы
		glLoadIdentity( );
	}

	void camera::view( void ) {

		// Обнуление матрицы MODELVIEW
		glLoadIdentity( );

		// Считаем матрицу MODELVIEW и устанавливаем трансформацию относительно камеры
		glm::mat4 lookat_mat = glm::lookAt( _position, _position + _center, _up );
		glLoadMatrixf( glm::value_ptr( lookat_mat ) );
	}

	// ==== GET / SET ====
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
	// ====================


}	// namespace demonblade
