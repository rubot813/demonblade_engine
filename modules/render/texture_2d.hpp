#ifndef TEXTURE_2D_HPP_INCLUDED
#define TEXTURE_2D_HPP_INCLUDED

#include "texture.hpp"
/*
	Класс texture_2d описывает одну двумерную текстуру. Координаты : u или s(x), v или t(y)
	Предоставляет методы для загрузки текстуры из RAM или файлов в VRAM и наоборот
*/

namespace demonblade {

	class texture_2d : public texture {

		public:

			texture_2d( void );

			~texture_2d( void );

			// Метод загрузки текстуры из памяти
			// Принимает указатель на массив и его ширину и длину
			bool load_from_memory(	const void *pixel_ptr, uint16_t width, uint16_t height,
			                        image::img_sized_format_e sized = image::SIZED_RGB,
			                        tex_filter_e filter_high = NEAREST,
			                        tex_filter_e filter_low = NEAREST,
			                        tex_wrap_e wrap_u = CLAMP,
			                        tex_wrap_e wrap_v = CLAMP );

			// Метод загрузки текстуры из изображения
			bool load_from_image(	image *img,
			                        tex_filter_e filter_high = NEAREST,
			                        tex_filter_e filter_low = NEAREST,
			                        tex_wrap_e wrap_u = CLAMP,
			                        tex_wrap_e wrap_v = CLAMP );

			// Метод получения количества текстурных координат
			uint8_t get_tex_coords_num( void );

	};	// class texture_2d

}	// namespace demonblade
#endif // TEXTURE_2D_HPP_INCLUDED
