#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <cstdint>	// C++11
#ifndef __GNUC__	// For VC
	#include <cstddef>
#endif
#include "../core/ogl.hpp"
#include "../utils/image.hpp"

/*
	Класс texture описывает базовый объект текстуры
*/

namespace demonblade {

	class texture {

		public:

			// Перечисление типов фильтрации текстуры
			enum tex_filter_e {
				NEAREST = 0x2600,		// Интерполяция по соседним текселям
				LINEAR	= 0x2601		// Билинейная фильтрация
			};

			// Перечисление типов наложения текстуры
			enum tex_wrap_e {
				CLAMP					= 0x2900,	// Вжатие текстуры в указанный диапазон
				MIRROR_CLAMP_TO_EDGE	= 0x8743,	// Вжатие текстуры в указанный диапазон с повторением
				REPEAT					= 0x2901,	// Повторение текстуры
				MIRRORED_REPEAT			= 0x8370,	// Отражение текстуры с повторением
				CLAMP_TO_BORDER			= 0x812D,	// Игнорирование текселей, выходящих за диапазон
				CLAMP_TO_EDGE			= 0x812E	// Игнорирование выборки текселей, выходящих за край
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
			texture_id	_texture_ptr;

			// Тип текстуры
			std::size_t	_type;

	};	// class texture

}	// namespace demonblade
#endif // TEXTURE_HPP_INCLUDED
