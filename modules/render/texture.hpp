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
			texture_id _texture_ptr;

			// Тип текстуры
			std::size_t		_type;

	};	// class texture

}	// namespace demonblade
#endif // TEXTURE_HPP_INCLUDED
