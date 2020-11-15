#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <cstdint>	// C++11

/*
	Класс texture описывает одну текстуру. Позволяет загружать набор пикселей из RAM в VRAM

	usage:
	db::texture *tex;
	tex = new db::texture;
	if ( tex.load_from_memory( ... ) ) {
		// ok!
	}
	model->set_texture( tex );
*/

// todo: 1d, 3d textures, mipmap, check on 64bit compiler

namespace demonblade {

	class texture {

		public:
			texture( void );
			~texture( void );

			// Перечисление типов фильтрации текстуры
			enum filter_e {
				NEAREST = 0x2600,		// Интерполяция по соседним текселям
				LINEAR	= 0x2601		// Билинейная фильтрация
			};

			// Перечисление типов наложения текстуры
			enum wrap_e {
				CLAMP					= 0x2900,	// Вжатие текстуры в указанный диапазон
				MIRROR_CLAMP_TO_EDGE	= 0x8743,	// Вжатие текстуры в указанный диапазон с повторением
				REPEAT					= 0x2901,	// Повторение текстуры
				MIRRORED_REPEAT			= 0x8370,	// Отражение текстуры с повторением
				CLAMP_TO_BORDER			= 0x812D,	// Игнорирование текселей, выходящих за диапазон
				CLAMP_TO_EDGE			= 0x812E	// Игнорирование выборки текселей, выходящих за край
			};

			// Перечисление форматов упаковки значений цветов пикселей
			// На данный момент есть поддержка только RGBA 8 / 32 бита
			enum pack_e {
				RGBA8			= 0x8058,	// RGBA, 8 бит / пиксель
				RGBA8_SNORM		= 0xF897,	// RGBA, 8 знаковых бит / пиксель
				RGBA16			= 0x805B,	// RGBA, 16 бит / пиксель
				SRGB8_ALPHA8	= 0x8C43,	// RGBA, 8 бит / пиксель
				RGBA32F			= 0x8814,	// RGBA, 32 бит с плавающей точкой / пиксель
				RGBA8I			= 0x8D8E,	// RGBA, 8i бит / пиксель
				RGBA32I			= 0x8D82,	// RGBA, 32i бит / пиксель
				RGBA32UI		= 0x8D70	// RGBA, 32ui бит / пиксель
			};

			// Алиас текстуры
			typedef std::size_t texture_t;

			// Метод с полным набором параметров
			// Загружает текстуру в VRAM
			bool load_from_memory( const void *pixel_ptr, uint16_t width, uint16_t height, pack_e pack = RGBA8,
			                       filter_e filter_high = NEAREST, filter_e filter_low = NEAREST,
			                       wrap_e wrap_u = CLAMP, wrap_e wrap_v = CLAMP );

			// Метод получения имени загруженой текстуры, используется в db::model
			texture_t* get_pointer( void );

		private:

			// Указатель на загруженную текстуру
			texture_t _texture_ptr;
	};	// class texture

}	// namespace demonblade
#endif // TEXTURE_HPP_INCLUDED
