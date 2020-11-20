#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include "../common/db_glm.hpp"
#include "../common/global.hpp"

/*
	Класс для базовой работы с камерой. Служит классом - родителем для
	других, более сложных типов камер
*/

namespace demonblade {

	class camera {
		public:

			camera( void );

			~camera( void );

			// Метод установки порта вывода
			// Все принимаемые параметры описаны в private
			void set_viewport( uint16_t width, uint16_t height, float fov = 60.0f, float z_near = 0.1f, float z_far = 250.0f );

			// Метод проецирования
			// Устанавливает матрицу modelview
			void view( void );

			// ====

			// Методы установки параметров камеры
			void set_position( glm::vec3 value );
			void set_center( glm::vec3 value );
			void set_up( glm::vec3 value );

			// Методы получения параметров камеры
			glm::vec3 get_position( void );
			glm::vec3 get_center( void );
			glm::vec3 get_up( void );

			// ====

			// Переменные
		protected:

			// Позиция камеры ( точка наблюдения )
			glm::vec3	_position;

			// Направление камеры
			glm::vec3	_center;

			// Вертикальный вектор. Должен быть { 0.0f, 1.0f, 0.0f }
			glm::vec3	_up;

	};	// camera class

}	// namespace demonblade

#endif // CAMERA_HPP_INCLUDED
