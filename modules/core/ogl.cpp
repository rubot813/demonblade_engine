#include "ogl.hpp"
#include "../common/gl_libs.hpp"

namespace demonblade {

	bool ogl::init( uint16_t viewport_width, uint16_t viewport_height, float fov ) {

		// Инициализация GLEW и обработка ошибки
		GLenum glew_init_error = glewInit( );

		if ( glew_init_error != GLEW_OK )
			return 0;

		// Инициализация OpenGL

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

		// Save vport params
		_viewport_height	= viewport_height;
		_viewport_width		= viewport_width;
		_fov				= fov;

		// Изменение размеров порта вывода
		reshape( );

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

	void ogl::reshape(  uint16_t new_viewport_width, uint16_t new_viewport_height ) {
		// Save vport params
		_viewport_height	= new_viewport_height;
		_viewport_width		= new_viewport_width;

		reshape( );
	}

	void ogl::reshape( void ) {
		// Установка положения и размера порта вывода
		glViewport( 0, 0, _viewport_width, _viewport_height );

		// Выбор матрицы проекции
		glMatrixMode( GL_PROJECTION );

		// Обнуление матрицы проекции
		glLoadIdentity( );

		// Расчет соотношения сторон экрана
		float aspect_ratio = ( ( float )_viewport_width / ( float )_viewport_height );

		// Определение матрицы наблюдения перспективной проекции ( GL_PROJECTION ):
		// Угол обзора по оси Y
		// Соотношение сторон экрана
		// Ближняя плоскость усеченной пирамиды наблюдения
		// Дальняя плоскость усеченной пирамиды наблюдения
		glm::mat4 projection_mat = glm::perspective( _fov, aspect_ratio, 1.0f, 250.0f );	// todo: magic nums?
		glLoadMatrixf( glm::value_ptr( projection_mat ) );

		// Выбор матрицы наблюдения моделей
		glMatrixMode( GL_MODELVIEW );

		// Обнуление матрицы
		glLoadIdentity( );
	}

	inline uint16_t ogl::get_viewport_height( void ) {
		return _viewport_height;
	}

	inline uint16_t ogl::get_viewport_width( void ) {
		return _viewport_width;
	}

	inline uint16_t ogl::get_fov( void ) {
		return _fov;
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
