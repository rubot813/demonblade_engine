#include "texture.hpp"
#include "../common/db_gl.hpp"

namespace demonblade {

	texture::texture( void ) {
		#ifdef __linux__
		_texture_ptr = 0;
		#endif
	}

	texture::~texture( void ) {
		if ( _texture_ptr )
			glDeleteTextures( 1, &_texture_ptr );
	}

	bool texture::load_from_memory( const void *pixel_ptr, uint16_t width, uint16_t height, pack_e pack,
	                                filter_e filter_high, filter_e filter_low,
	                                wrap_e wrap_u, wrap_e wrap_v ) {

		// Генерация имени текстуры: заносит в _texture_ptr имя сгенерированной текстуры
		glGenTextures( 1, &_texture_ptr );

		// Установка текстуры ( все следующие операции будут производиться над ней )
		glBindTexture( GL_TEXTURE_2D, _texture_ptr );

		// Загрузка текстуры в VRAM
		glTexImage2D( GL_TEXTURE_2D,
		              0,
		              pack,					// Тип упаковки бит
		              width,				// Ширина
		              height,				// Длина
		              0,
		              GL_RGBA,
		              GL_UNSIGNED_BYTE,
		              pixel_ptr );			// Указатель на массив байт пикселей

		// Настройка параметра фильтрации текстуры
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_high );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_low );

		// Настройка параметра наложения текстуры
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_u );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_v );

		return ( ( bool )_texture_ptr );
	}

	texture::texture_t* texture::get_pointer( void ) {
		return &_texture_ptr;
	}
}	// namespace demonblade
