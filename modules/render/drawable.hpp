#ifndef DRAWABLE_HPP_INCLUDED
#define DRAWABLE_HPP_INCLUDED

#include "../common/global.hpp"
#include "../common/db_glm.hpp"

namespace demonblade {
	class drawable {

		public:

			// Методы перемещения, вращения и масштабирования
			void move( glm::vec3 offset );
			void rotate( glm::vec3 offset );
			void scale( glm::vec3 offset );

			// Методы установки позиции, поворота и масштаба
			void set_position( glm::vec3 value );
			void set_rotation( glm::vec3 value );
			void set_scale( glm::vec3 value );

			// Методы получения позиции, поворота и масштаба
			glm::vec3 get_position( void );
			glm::vec3 get_rotation( void );
			glm::vec3 get_scale( void );

			// Методы установки световых параметров
			void set_ambient( glm::vec4 value );
			void set_diffuse( glm::vec4 value );
			void set_specular( glm::vec4 value );

			// Методы получения световых параметров
			glm::vec4 get_ambient( void );
			glm::vec4 get_diffuse( void );
			glm::vec4 get_specular( void );

			// Метод отрисовки
			virtual void render( void );

		protected:

			// Базовые параметры: положение, вращение и масштабирование
			glm::vec3 _position;
			glm::vec3 _rotation;
			glm::vec3 _scale;

			// Световые параметры
			glm::vec4 _ambient;		// Рассеянный свет
			glm::vec4 _diffuse;		// Диффузный свет
			glm::vec4 _specular;	// Отраженный свет

	};	// class drawable

}	// namespace demonblade

#endif // DRAWABLE_HPP_INCLUDED
