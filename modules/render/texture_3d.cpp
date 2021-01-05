#include "texture_3d.hpp"
#include "../common/db_gl.hpp"

namespace demonblade {

	texture_3d::texture_3d( void ) {
		_type = ogl::TEXTURE_3D;
		_texture_ptr = 0;
	}

	texture_3d::~texture_3d( void ) {
		if ( _texture_ptr )
			glDeleteTextures( 1, &_texture_ptr );
	}

	bool texture_3d::load_from_memory( 	const void *pixel_ptr, uint16_t width, uint16_t height, uint16_t depth,
	                                    image::img_sized_format_e sized,
	                                    tex_filter_e filter_high,
	                                    tex_filter_e filter_low,
	                                    tex_wrap_e wrap_s,
	                                    tex_wrap_e wrap_t,
	                                    tex_wrap_e wrap_r ) {

		// Определение базового формата изображения
		image::img_base_format_e base = image::get_base_pixel_format( sized );

		// Генерация имени текстуры: заносит в _texture_ptr имя сгенерированной текстуры
		glGenTextures( 1, &_texture_ptr );

		// Установка текстуры
		bind( );

		// Загрузка текстуры в VRAM
		glTexImage3D( _type,				// 3D
		              0,					// Mipmap level
		              sized,				// Тип упаковки бит
		              width,				// Ширина
		              height,				// Длина
		              depth,				// Глубина
		              0,					// Смещение в массиве байт
		              base,					// Формат пикселей
		              GL_UNSIGNED_BYTE,		// Формат данных
		              pixel_ptr );			// Указатель на массив байт пикселей

		// Настройка параметров фильтрации текстуры
		glTexParameteri( _type, GL_TEXTURE_MAG_FILTER, filter_high );
		glTexParameteri( _type, GL_TEXTURE_MIN_FILTER, filter_low );

		// Настройка параметров наложения текстуры
		glTexParameteri( _type, GL_TEXTURE_WRAP_S, wrap_s );
		glTexParameteri( _type, GL_TEXTURE_WRAP_T, wrap_t );
		glTexParameteri( _type, GL_TEXTURE_WRAP_R, wrap_r );

		return ( ( bool )_texture_ptr );
	}

	uint8_t texture_3d::get_tex_coords_num( void ) {
		return ( uint8_t )3;
	}

}	// namespace demonblade
