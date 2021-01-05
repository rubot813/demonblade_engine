#ifndef FP_CAMERA_HPP_INCLUDED
#define FP_CAMERA_HPP_INCLUDED

#include "camera.hpp"

/*
	Класс реализует работу камеры от первого лица ( first - person camera )
	Основан на базовой камере camera
*/

namespace demonblade {

	class fp_camera : public camera {
		public:

			fp_camera( void );

			~fp_camera( void );

			// Методы передвижения камеры относительно направления взгляда
			// Принимают дельту ( скорость ) на сколько передвинуться
			void move_backward( float delta );
			void move_forward( float delta );
			void move_left( float delta );
			void move_right( float delta );
			void move_down( float delta );
			void move_up( float delta );

			// Метод установки угла поворота камеры
			// Принимает углы в градусах
			void set_angle( glm::vec2 angle );

			// Метод получения угла повороты камеры
			// Возвращает значение в градусах
			glm::vec2 get_angle( void );

			// Метод добавления угла к углу вращения камеры
			void add_angle( glm::vec2 val );

			// Метод ограничивает вертикальный угол поворота камеры
			void constraint_pitch( float y_up = 0.027f, float y_down = -0.027f );

			// Метод расчета вектора направления камеры по заданным углам Эйлера
			void calc_center( void );

		private:

			// Вектор, описывающий углы поворота камеры ( углы Эйлера )
			// x : yaw ( горизонтальная ось )
			// y : pitch ( вертикальная ось )
			glm::vec2 _angle;

	};	// fp_camera class

}	// namespace demonblade

#endif // CAMERA_HPP_INCLUDED
