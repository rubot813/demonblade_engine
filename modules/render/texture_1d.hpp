#ifndef TEXTURE_1D_HPP_INCLUDED
#define TEXTURE_1D_HPP_INCLUDED

#include "texture.hpp"
/*
	Класс texture_1d описывает объект одномерной текстуры. Текстурные координаты: s( x )
	Предоставляет методы для загрузки текстуры из RAM
*/

namespace demonblade {

	class texture_1d : public texture {

		public:

			texture_1d( void );

			~texture_1d( void );

			// Метод загрузки 1d текстуры из памяти
			// Принимает указатель на массив и его размер в байтах
			bool load_from_memory(	const void *pixel_ptr, uint16_t width,
			                        image::img_sized_format_e sized = image::SIZED_RGB,
			                        tex_filter_e filter_high = NEAREST,
			                        tex_filter_e filter_low = NEAREST,
			                        tex_wrap_e wrap_s = CLAMP );

			// Метод получения количества текстурных координат
			uint8_t get_tex_coords_num( void );

	};	// class texture_1d

}	// namespace demonblade
#endif // TEXTURE_1D_HPP_INCLUDED
