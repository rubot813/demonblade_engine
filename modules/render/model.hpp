#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "drawable.hpp"
#include "texture.hpp"
#include "mesh.hpp"

#include <sstream>
#include <list>

/*
	 ласс, позвол€ющий универсально работать с модел€ми и текстурами разных форматов.
	ћодель состоит из меша ( геометрии ) и текстуры
*/


namespace demonblade {
	//  ласс описывает одну модель
	class model : public drawable {

		public:
			model( void );
			~model( void );

			// ћетод установки текстуры и меша модели
			// ƒл€ инициализации модели рекомендуетс€ использовать его
			// ¬ернет true если все корректно и охуенно ( просто и гениально )
			// ¬ернет false если не хватает пам€ти,
			// если указатели на валидны,
			// если меш не загружен в RAM,
			// если текстура не загружена в VRAM
			bool set_data( mesh *mesh_ptr, texture *tex_ptr );

			// ћетоды установки текстуры и меша модели по отдельности
			bool set_mesh( mesh *mesh_ptr );
			bool set_texture( texture *tex_ptr );

			// ћетоды получени€ указателей на меш и текстуру модели
			mesh*				get_mesh( void );
			texture*			get_texture( void );

			// ћетод отрисовки модели или ее части
			void render( void );	// virtual

		private:

			// ћеш модели
			mesh				_mesh;

			// “екстура и им€ текстуры модели
			texture				*_texture;
			texture::texture_t	*_texture_name;

	};	// class model

}	// namespace demonblade

#endif // MODEL_HPP_INCLUDED
