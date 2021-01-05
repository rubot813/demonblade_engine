#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <cstdint>	// C++11
#ifndef __GNUC__	// For VC
	#include <cstddef>
#endif
#include "../core/ogl.hpp"
#include "../utils/image.hpp"

/*
	 ласс texture описывает базовый объект текстуры
*/

namespace demonblade {

	class texture {

		public:

			// ѕеречисление типов фильтрации текстуры
			enum tex_filter_e {
				NEAREST = 0x2600,		// »нтерпол¤ци¤ по соседним тексел¤м
				LINEAR	= 0x2601		// Ѕилинейна¤ фильтраци¤
			};

			// ѕеречисление типов наложени¤ текстуры
			enum tex_wrap_e {
				CLAMP					= 0x2900,	// ¬жатие текстуры в указанный диапазон
				MIRROR_CLAMP_TO_EDGE	= 0x8743,	// ¬жатие текстуры в указанный диапазон с повторением
				REPEAT					= 0x2901,	// ѕовторение текстуры
				MIRRORED_REPEAT			= 0x8370,	// ќтражение текстуры с повторением
				CLAMP_TO_BORDER			= 0x812D,	// »гнорирование текселей, выход¤щих за диапазон
				CLAMP_TO_EDGE			= 0x812E	// »гнорирование выборки текселей, выход¤щих за край
			};

			// јлиас текстуры, чтобы не светить GLuint
			typedef std::size_t texture_id;

			// ћетод установки текстуры
			void bind( void );

			// ћетод получени¤ количества текстурных координат
			virtual uint8_t get_tex_coords_num( void );

			// ћетод получени¤ указател¤ на идентификатор загруженой текстуры
			texture_id* get_pointer( void );

		protected:

			// »дентификатор загруженной текстуры
			texture_id	_texture_ptr;

			// “ип текстуры
			std::size_t	_type;

	};	// class texture

}	// namespace demonblade
#endif // TEXTURE_HPP_INCLUDED
