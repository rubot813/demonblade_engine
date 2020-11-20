#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "model_part.hpp"

#include <sstream>
#include <list>

/*
	Класс, позволяющий универсально работать с моделями и текстурами разных форматов.
	Модель состоит из частей ( part ). Часть модели состоит из меша ( геометрии ) и текстуры.
*/

// todo: render from container
// todo: i_drawable

namespace demonblade {
	// Класс описывает одну модель
	class model {

		public:
			model( void );
			~model( void );

			// Метод добавления текстуры и меша модели
			// Добавляются в модель в виде части
			// Вернет true если все корректно и охуенно ( просто и гениально )
			// Вернет false если не хватает памяти,
			// если указатели на валидны,
			// если меш не загружен в RAM,
			// если текстура не загружена в VRAM
			bool add_part( mesh *mesh_ptr, texture *tex_ptr );

			// Метод удаления части модели по id
			// Вернет true если успешно
			// Вернет false если часть не существует или out of range
			bool remove_part( std::size_t id );

			// Метод получения количества частей модели
			std::size_t get_part_count( void );

			// Методы получения указателей на меш и текстуру модели
			// Принимают порядковый номер части модели
			mesh*		get_mesh( std::size_t id );
			texture*	get_texture( std::size_t id );

			// Методы перемещения, вращения и масштабирования модели
			void move( glm::vec3 offset );
			void rotate( glm::vec3 offset );
			void scale( glm::vec3 offset );

			// Методы установки позиции, поворота и масштаба модели
			void set_position( glm::vec3 value );
			void set_rotation( glm::vec3 value );
			void set_scale( glm::vec3 value );

			// Методы получения позиции, поворота и масштаба модели
			glm::vec3 get_position( void );
			glm::vec3 get_rotation( void );
			glm::vec3 get_scale( void );

			// Метод отрисовки всей модели или ее части
			void render( void );
			void render( std::size_t id );

		private:

			// Внутренний метод отрисовки части модели через указатель
			void _render( model_part *part_ptr );

			// Метод получения итератора на элемент model_part по индексу
			// Своя замена std::list::at
			std::list< model_part >::iterator _get_part_iterator( std::size_t index );

			// Базовые параметры модели: положение, вращение и масштабирование
			glm::vec3 _position;
			glm::vec3 _rotation;
			glm::vec3 _scale;

			// Световые параметры модели
			glm::vec4 _ambient;		// Рассеянный свет
			glm::vec4 _diffuse;		// Диффузный свет
			glm::vec4 _specular;	// Отраженный свет

			// Контейнер с частями модели
			std::list< model_part > _part;

	};	// class model

}	// namespace demonblade

#endif // MODEL_HPP_INCLUDED
