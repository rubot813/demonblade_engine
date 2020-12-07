#include "ogl.hpp"
#include "../common/db_gl.hpp"

namespace demonblade {

	bool ogl::init( void  ) {

		// Инициализация GLEW и обработка ошибки
		GLenum glew_init_error = glewInit( );

		if ( glew_init_error != GLEW_OK ) {
			db_dbg_error( "init GLEW error\n" );
			return 0;
		}

		// Базовая настройка OpenGL

		// Установка цвета очистки порта вывода в RGBA
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

		// Установка глубины очистки
		glClearDepth( 1.0f );

		// Включение теста глубины
		glEnable( GL_DEPTH_TEST );

		// Функция теста глубины: объект будет отображаться только если он ближе к камере
		glDepthFunc( GL_LESS );

		// Включение отсечения невидимых граней
		//glEnable( GL_CULL_FACE );

		// Автоматическое преобразование всех нормалей в единичные
		//glEnable( GL_NORMALIZE );
		//glEnable( GL_RESCALE_NORMAL );

		// Настройка функции альфа теста
		glAlphaFunc( GL_GREATER, 0 );

		// Выбор матрицы наблюдения моделей
		// Чтобы не упали, если выбрана другая
		glMatrixMode( GL_MODELVIEW );

		db_dbg_msg( "init ok\n" );

		return 1;
	}

	void ogl::enable( func_e type ) {
		glEnable( type );
	}

	void ogl::disable( func_e type ) {
		glDisable( type );
	}

	void ogl::select( func_e type, bool state ) {
		state ? glEnable( type ) : glDisable( type );
	}

	void ogl::clear( void ) {
		// Очистка буфера глубины и цвета
		//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		// Очистка буфера глубины
		glClear( GL_DEPTH_BUFFER_BIT );
	}

	void fog::set( float start, float end, float density ) {
		// Enable fog
		// ogl::get_instance( ).enable( ogl::FOG );

		//Начало
		glFogf( GL_FOG_START, ( GLfloat )start);

		//Конец
		glFogf( GL_FOG_END, ( GLfloat )end );

		//Плотность
		glFogf( GL_FOG_DENSITY, ( GLfloat ) density );
	}

} //namespace demonblade
