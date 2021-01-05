#ifndef SPRITE_HPP_INCLUDED
#define SPRITE_HPP_INCLUDED

#include "drawable.hpp"
#include "texture.hpp"
/*
	Класс, позволяющий работать со спрайтами - графическими объектами,
	которые всегда повернуты к камере
*/

namespace demonblade {
	// Класс описывает один спрайт
	class sprite : public drawable {

		public:

			// Типы спрайтов
			typedef enum {
				// Сферический: всегда направлен к камере
				SPHERICAL,

				// Цилиндрически: направлен к камере по оси x
				CYLINDRICAL

			} type_e;

			sprite( void );
			~sprite( void );

			// Метод установки данных спрайта
			// Возвращает 1 если все успешно
			bool set_data( type_e type, glm::vec2 size, texture *tex_ptr );


			// Методы установки и получения типа спрайта
			void set_type( type_e type );
			type_e get_type( void );

			// Методы установки и получения размера спрайта
			void set_size( glm::vec2 size );
			glm::vec2 get_size( void );


			// Методы установки и получения текстуры
			bool set_texture( texture *tex_ptr );
			texture*	get_texture( void );


			// Метод отрисовки
			void render( void );	// virtual

		private:

			// Размер
			glm::vec2			_size;

			// Тип
			type_e				_type;

			// Вершины и текстурные координаты
			glm::vec3			_vertex[ 6 ];
			glm::vec2			_texel[ 6 ];

			// Текстура и имя текстуры
			texture				*_texture;
			texture::texture_id	*_texture_id;

	};	// class sprite

}	// namespace demonblade

#endif // SPRITE_HPP_INCLUDED
