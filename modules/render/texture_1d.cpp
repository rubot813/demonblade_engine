#include "texture_1d.hpp"
#include "../common/db_gl.hpp"

namespace demonblade {

	texture_1d::texture_1d( void ) {
		_type = ogl::TEXTURE_1D;
		_texture_ptr = 0;
	}

	texture_1d::~texture_1d( void ) {
		if ( _texture_ptr )
			glDeleteTextures( 1, &_texture_ptr );
	}

	bool texture_1d::load_from_memory( const void *pixel_ptr, uint16_t width, pack_e pack,
	                                   filter_e filter_high, filter_e filter_low,
	                                   wrap_e wrap_s ) {

		// Генерация имени текстуры: заносит в _texture_ptr имя сгенерированной текстуры
		glGenTextures( 1, &_texture_ptr );

		// Установка текстуры
		bind( );

		// Загрузка текстуры в VRAM
		glTexImage1D( _type,				// 1D
		              0,					// Mipmap level
		              pack,					// Тип упаковки бит
		              width,				// Ширина
		              0,					// Смещение в массиве байт
		              GL_RGBA,				// Формат пикселей
		              GL_UNSIGNED_BYTE,		// Формат данных
		              pixel_ptr );			// Указатель на массив байт пикселей

		// Настройка параметров фильтрации текстуры
		glTexParameteri( _type, GL_TEXTURE_MAG_FILTER, filter_high );
		glTexParameteri( _type, GL_TEXTURE_MIN_FILTER, filter_low );

		// Настройка параметра наложения текстуры
		glTexParameteri( _type, GL_TEXTURE_WRAP_S, wrap_s );

		return ( ( bool )_texture_ptr );
	}

	uint8_t texture_1d::get_tex_coords_num( void ) {
		return ( uint8_t )1;
	}
}	// namespace demonblade
