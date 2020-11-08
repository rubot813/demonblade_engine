#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include "../common/gl_libs.hpp"

/*
	Класс реализует работу камеры
*/

namespace demonblade {

	class camera {
		public:
			// Конструктор по умолчанию
			camera( void );

			// Перегруженный конструктор, просто вызывает set_viewport
			camera( uint16_t width, uint16_t height, float fov, float z_near = 1.0f, float z_far = 250.0f );

			~camera( void );

			// Методы установки параметров камеры
			inline void set_position( glm::vec3 value );
			inline void set_center( glm::vec3 value );
			inline void set_up( glm::vec3 value );

			// Методы получения параметров камеры
			inline glm::vec3 get_position( void );
			inline glm::vec3 get_center( void );
			inline glm::vec3 get_up( void );

			// Метод установки порта вывода
			// Все принимаемые параметры описаны в private
			void set_viewport( uint16_t width, uint16_t height, float fov, float z_near = 1.0f, float z_far = 250.0f );

			// Метод проецирования от лица текущей камеры
			void project( void );

			// Методы
		private:
			// Метод устанавливает матрицу проекции GL_PROJECTION по параметрам порта вывода
			void _set_projection_matrix( void );


			// Переменные
		private:

			// Позиция камеры ( точка наблюдения )
			glm::vec3	_position;

			// Угол поворта камеры ( центр наблюдения )
			glm::vec3	_center;

			// Направление камеры вверх
			glm::vec3	_up;

			// Размеры порта вывода
			uint16_t	_viewport_width;
			uint16_t	_viewport_height;

			// Угол обзора в градусах
			float	_fov;

			// Ближняя и дальняя плоскости пирамиды видимости
			float		_z_near;
			float		_z_far;

	};	// camera class

}	// namespace demonblade

#endif // CAMERA_HPP_INCLUDED
