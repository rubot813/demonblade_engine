#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <cstdint>	// C++11
#ifndef __GNUC__	// For VC
	#include <cstddef>
#endif
#include "../core/ogl.hpp"

/*
	Класс texture описывает базовый объект текстуры
*/

namespace demonblade {

	class texture {

		public:

			// Алиас текстуры, чтобы не светить GLuint
			typedef std::size_t texture_id;

			// Метод установки текстуры
			void bind( void );

			// Метод получения количества текстурных координат
			virtual uint8_t get_tex_coords_num( void );

			// Метод получения указателя на идентификатор загруженой текстуры
			texture_id* get_pointer( void );

		protected:

			// Идентификатор загруженной текстуры
			texture_id	_texture_ptr;

			// Тип текстуры
			std::size_t	_type;

	};	// class texture

}	// namespace demonblade
#endif // TEXTURE_HPP_INCLUDED
