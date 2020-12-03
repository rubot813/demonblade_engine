#ifndef OGL_HPP_INCLUDED
#define OGL_HPP_INCLUDED

/*
    Хэдер для подключения модуля работы с OpenGL движка demonblade
    Реализует класс - одиночку для работы с функциями состояний OpenGL

    Использование:
    db::ogl::get_instance( )-><method>( );
*/

#include <cstdint>
#include "../common/global.hpp"

// todo: light

namespace demonblade {

	class ogl {
		public:
			// Перечисление функций ядра
			enum func_e {
				TEXTURE_1D			=	0x0DE0,	// Текстуры по количеству измерений
				TEXTURE_2D			=	0x0DE1,
				TEXTURE_3D			=	0x806F,
				TEXTURE_CUBE_MAP	=	0x8513,	// Кубическая текстура
				LIGHT				=	0x0B50,	// Свет
				ALPHA_TEST			=	0x0BC0,	// Альфа тест ( спрайты, текстуры )
				FOG					=	0x0B60,	// Туман
				CULL				=	0x0B44,	// Отсечение невидимых граней
				DITHERING			=	0x0BD0	// Смешивание цветов при отрисовке
				                        // todo GL_TEXTURE_CUBEMAP_SEAMLESS
				                        // todo DEPTH MASK
			};

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

			// Перечисление базовых форматов упаковки пикселей
			enum tex_base_format_e {
				RGB		= 0x1907,	// R G B
				RGBA	= 0x1908	// R G B A
			};

			// Перечисление расширенных форматов упаковки пикселей
			enum tex_sized_format_e {
				RGBA8	= 0x8058,	// RGBA, 8 бит / пиксель
				RGBA16	= 0x805B,	// RGBA, 16 бит / пиксель
				RGBA32F	= 0x8814,	// RGBA, 32 бит с плавающей точкой / пиксель
			};

			static ogl* get_instance( void ) {
				static ogl ogl_instance;	// lazy :<
				return &ogl_instance;
			}

			// Функция инициализации ядра OpenGL
			// Возвращает true, если успешно
			bool init( void );

			// Функция очистки матрицы MODELVIEW и буферов OpenGL
			void clear( void );

			// Функции включения / выключения возможностей OpenGL
			void enable( func_e type );
			void disable( func_e type );
			void select( func_e type, bool state );

		private:
			// Запрет конструктора, деструктора, операции копирования
			ogl( void ) { };
			~ogl( void ) { };
			ogl( const ogl &_ex ) = delete;
			ogl& operator=( const ogl& ) = delete;
	};	// ogl

	namespace fog {
		// Установка параметров тумана
		// Начало, конец, плотность
		void set( float start, float end, float density );

	}	// namespace fog

	namespace light {
		// todo
	}	// namespace light

} // namespace demonblade

#endif // OGL_HPP_INCLUDED
