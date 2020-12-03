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
									ogl::tex_base_format_e base = ogl::RGBA,
									ogl::tex_sized_format_e sized = ogl::RGBA8,
									ogl::tex_filter_e filter_high = ogl::NEAREST,
									ogl::tex_filter_e filter_low = ogl::NEAREST,
									ogl::tex_wrap_e wrap_s = ogl::CLAMP );

			// Метод получения количества текстурных координат
			uint8_t get_tex_coords_num( void );

	};	// class texture_1d

}	// namespace demonblade
#endif // TEXTURE_1D_HPP_INCLUDED
