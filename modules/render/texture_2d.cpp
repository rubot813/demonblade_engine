#include "texture_2d.hpp"
#include "../common/db_gl.hpp"

namespace demonblade {

	texture_2d::texture_2d( void ) {
		_type = ogl::TEXTURE_2D;
		_texture_ptr = 0;
	}

	texture_2d::~texture_2d( void ) {
		if ( _texture_ptr )
			glDeleteTextures( 1, &_texture_ptr );
	}

	bool texture_2d::load_from_memory(	const void *pixel_ptr, uint16_t width, uint16_t height,
	                                    image::img_sized_format_e sized,
	                                    tex_filter_e filter_high,
	                                    tex_filter_e filter_low,
	                                    tex_wrap_e wrap_u,
	                                    tex_wrap_e wrap_v ) {

		// Определение базового формата изображения
		image::img_base_format_e base = image::get_base_pixel_format( sized );

		// Генерация имени текстуры: заносит в _texture_ptr имя сгенерированной текстуры
		glGenTextures( 1, &_texture_ptr );

		// Установка текстуры
		bind( );

		// Загрузка текстуры в VRAM
		glTexImage2D( _type,				// 2D
		              0,					// Mipmap level
		              sized,				// Тип упаковки бит
		              width,				// Ширина
		              height,				// Длина
		              0,					// Смещение в массиве байт
		              base,					// Формат пикселей
		              GL_UNSIGNED_BYTE,		// Формат данных
		              pixel_ptr );			// Указатель на массив байт пикселей

		// Настройка параметров фильтрации текстуры
		glTexParameteri( _type, GL_TEXTURE_MAG_FILTER, filter_high );
		glTexParameteri( _type, GL_TEXTURE_MIN_FILTER, filter_low );

		// Настройка параметров наложения текстуры
		glTexParameteri( _type, GL_TEXTURE_WRAP_S, wrap_u );
		glTexParameteri( _type, GL_TEXTURE_WRAP_T, wrap_v );

		return ( ( bool )_texture_ptr );
	}

	bool texture_2d::load_from_image(	image *img,
	                                    tex_filter_e filter_high,
	                                    tex_filter_e filter_low,
	                                    tex_wrap_e wrap_u,
	                                    tex_wrap_e wrap_v ) {
		bool ok = 0;
		if ( img ) {
			if ( load_from_memory(	img->get_data_ptr( ),
			                        img->get_width( ),
			                        img->get_height( ),
			                        img->get_pixel_format( ),
			                        filter_high,
			                        filter_low,
			                        wrap_u,
			                        wrap_v ) ) {

				ok = 1;
			}	// if load_from_memory
		}	// if img

		return ok;
	}

	uint8_t texture_2d::get_tex_coords_num( void ) {
		return ( uint8_t )2;
	}
}	// namespace demonblade
