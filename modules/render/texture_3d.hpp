#ifndef TEXTURE_3D_HPP_INCLUDED
#define TEXTURE_3D_HPP_INCLUDED

#include "texture.hpp"
/*
	Класс texture_3d описывает одну трехмерную текстуру. Координаты : s(x), t(y), r(z)
	Предоставляет методы для загрузки текстуры из RAM или файлов в VRAM и наоборот
*/

namespace demonblade {

	class texture_3d : public texture {

		public:

			texture_3d( void );

			~texture_3d( void );

			// Метод загрузки текстуры из памяти
			// Принимает указатель на массив и его ширину, длину и глубину
			// Пока что только базовая обертка, но она должна работать
			bool load_from_memory( 	const void *pixel_ptr, uint16_t width, uint16_t height, uint16_t depth,
									ogl::tex_base_format_e base = ogl::RGBA,
									ogl::tex_sized_format_e sized = ogl::RGBA8,
									ogl::tex_filter_e filter_high = ogl::NEAREST,
									ogl::tex_filter_e filter_low = ogl::NEAREST,
									ogl::tex_wrap_e wrap_s = ogl::CLAMP,
									ogl::tex_wrap_e wrap_t = ogl::CLAMP,
									ogl::tex_wrap_e wrap_r = ogl::CLAMP  );

			// Метод получения количества текстурных координат
			uint8_t get_tex_coords_num( void );

	};	// class texture_3d

}	// namespace demonblade
#endif // TEXTURE_3D_HPP_INCLUDED
