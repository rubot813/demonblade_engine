#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <cstdint>	// C++11

// todo: 1d, 3d textures, mipmap

namespace demonblade {
	// Класс описывает одну текстуру
	class texture {
		public:

			// Перечисление типов фильтрации текстуры
			enum filter_e {
				NEAREST = 0x2600,		// Интерполяция по соседним текселям
				LINEAR	= 0x2601		// Билинейная фильтрация
			};

			// Перечисление типов наложения текстуры
			enum wrap_e {

				// Вжатие текстуры в указанный диапазон
				CLAMP = 0x2900,

				// Вжатие текстуры в указанный диапазон с повторением
				MIRROR_CLAMP_TO_EDGE = 8743,

				// Повторение текстуры
				REPEAT =  0x2901,

				// Отражение текстуры с повторением
				MIRRORED_REPEAT = 0x8370,

				// Игнорирование текселей, выходящих за диапазон
				CLAMP_TO_BORDER = 0x812D,

				// Игнорирование выборки текселей, выходящих за край
				CLAMP_TO_EDGE = 0x812E,
			};

			// Тип текстуры DB. Осторожно - не будет работать на 64бит компиляторе
			typedef uint32_t texture_t;

			// Пустой конструктор по умолчанию
			texture( void );

			// Конструктор с полным набором параметров
			// Загружает текстуру в VRAM
			texture( const uint8_t *pixel_ptr, uint16_t width, uint16_t height,
			         filter_e filter_high = NEAREST, filter_e filter_low = NEAREST,
			         wrap_e wrap_u = CLAMP, wrap_e wrap_v = CLAMP );

			~texture( void );

			// Установка типов фильтрации текстуры
			// filter_high	- тип фильтрации когда изображение на экране больше, чем ее реальный размер
			// filter_low	- тип фильтрации когда изображение на экране меньше, чем ее реальный размер
			void set_filter_type( filter_e filter_high = NEAREST, filter_e filter_low = NEAREST );

			// Установка типа наложения текстуры
			// u и v - текстурные координаты 2D, направление соответствует x, y
			void set_wrap_type( wrap_e wrap_u = CLAMP, wrap_e wrap_v = CLAMP );

			// Установка указателя на двумерный массив RGBA ( по 8 бит на компоненту ) и размеров массива
			void set_pixel_pointer( const uint8_t *pixel_ptr, uint16_t width, uint16_t height );

			// Загрузка текстуры в видеокарту с указанными ранее параметрами
			// Вернет true в случае успешной загрузки
			bool load_to_vram( void );

			// Выгрузка текстуры из видеокарты
			void unload_from_vram( void );

			// Метод проверки, загружена ли текстура в VRAM
			bool is_loaded( void );

			// Метод получения указателя на загруженную текстуру
			texture_t* get_pointer( void );

		private:

			// Внутренние методы передачи в OpenGL указанных параметров
			void _generate_and_apply_texture( void );
			void _apply_filter( void );
			void _apply_wrap( void );

			// Указатель на массив пикселей
			uint8_t		*_pixel_ptr;

			// Размеры массива пикселя. Итоговый размер будет _pixel_width * _pixel_height
			uint16_t	_pixel_width;
			uint16_t	_pixel_height;

			// Типы фильтрации текстуры
			filter_e _filter_high;
			filter_e _filter_low;

			// Типы наложения текстуры по координатам U, V
			wrap_e _wrap_u;
			wrap_e _wrap_v;

			// Указатель на загруженную текстуру
			texture_t *_texture_ptr;

	};

}	// namespace demonblade
#endif // TEXTURE_HPP_INCLUDED
