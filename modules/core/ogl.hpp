#ifndef OGL_HPP_INCLUDED
#define OGL_HPP_INCLUDED

/*
    Хэдер для подключения модуля работы с OpenGL движка demonblade
    Реализует класс - одиночку для работы с функциями состояний OpenGL

    Использование:
    db::ogl::get_instance( )-><method>( );
*/

#include <cstdint>

// todo: light

namespace demonblade {

	class ogl {
		public:
			static ogl* get_instance( void ) {
				static ogl ogl_instance;	// lazy :<
				return &ogl_instance;
			}

			// Перечисление функций ядра
			enum func_e {
				TEXTURE_2D	= 0x0DE1,	// Текстуры 2D
				LIGHT		= 0x0B50,	// Свет
				ALPHA_TEST	= 0x0BC0,	// Альфа тест ( спрайты, текстуры )
				FOG			= 0x0B60,	// Туман
				CULL		= 0x0B44,	// Отсечение невидимых граней
				DITHERING	= 0x0BD0	// Смешивание цветов при отрисовке
			};

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
