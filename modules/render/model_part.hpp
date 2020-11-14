#ifndef MODEL_PART_HPP_INCLUDED
#define MODEL_PART_HPP_INCLUDED

#include <cstdint>	// C++11
#include "texture.hpp"
#include "mesh.hpp"

/*

	 ласс описывает часть модели, состо€ющую из меша и текстуры

	usage:
	db::model_part *mpart;
	mpart = new model_part( ... );
	if ( mpart->is_data_valid( ) ) {
			// ok!
	}

*/

namespace demonblade {

	class model_part {

		public:
			//  онструктор с передачей в класс указателей на меш и текстуру
			model_part( mesh *mesh_ptr, texture *tex_ptr );
			~model_part( void );

			// ћетод вернет true, если переданные в конструкторе данные валидны
			bool is_data_valid( void );

			// ћетод получени€ указател€ на меш
			mesh* get_mesh_ptr( void );

			// ћетод получени€ указател€ экземпл€р db::texture
			texture* get_texture_ptr( void );

			// ћетод получени€ указател€ на им€ текстуры
			texture::texture_t* get_texture_name_ptr( void );

		private:

			// Ёкземпл€р меша
			mesh		_mesh;

			// ”казатель на экземпл€р db::texture
			texture		*_texture;

			// ”казатель на поле name текстуры ( VRAM )
			texture::texture_t	*_texture_name;

	};	// class model_part

}	// namespace demonblade
#endif // MODEL_PART_HPP_INCLUDED
