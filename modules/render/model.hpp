#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "drawable.hpp"
#include "texture.hpp"
#include "mesh.hpp"

#include <sstream>
#include <list>

/*
	Класс, позволяющий универсально работать с моделями и текстурами разных форматов.
	Модель состоит из меша ( геометрии ) и текстуры
	Важно - с версии 0.982 модель хранит указатель на меш, а не копирует его себе
*/


namespace demonblade {
	// Класс описывает одну модель
	class model : public drawable {

		public:
			model( void );
			~model( void );

			// Метод установки текстуры и меша модели
			bool set_data( mesh *mesh_ptr, texture *tex_ptr );

			// Методы установки текстуры и меша модели по отдельности
			bool set_mesh( mesh *mesh_ptr );
			bool set_texture( texture *tex_ptr );

			// Методы получения указателей на меш и текстуру модели
			mesh*		get_mesh( void );
			texture*	get_texture( void );

			// Метод отрисовки модели или ее части
			void render( void );

		private:

			// Меш модели
			mesh				*_mesh;

			// Текстура модели
			texture				*_texture;
	};	// class model

}	// namespace demonblade

#endif // MODEL_HPP_INCLUDED
