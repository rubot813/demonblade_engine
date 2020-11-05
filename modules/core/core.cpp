#include "core.hpp"
#include "../common/include_gl.hpp"

namespace demonblade {

bool core::init( uint16_t window_width, uint16_t window_height ) {

	// Инициализация GLEW и обработка ошибки
	GLenum glew_init_error = glewInit( );
	if ( glew_init_error != GLEW_OK )
		return 0;

	// Инициализация OpenGL

	// Установка цвета очистки порта вывода в RGBA
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	// Установка глубины очистки
	glClearDepth( 1.0d );

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

	// Изменение размеров порта вывода
	reshape( window_width, window_height );

	return 1;
}

void core::enable( func_e type ) {
	glEnable( type );
}

void core::disable( func_e type ) {
	glDisable( type );
}

void core::select( func_e type, bool state ) {
	state ? glEnable( type ) : glDisable( type );
}

void core::clear( void ) {
	// Очистка буфера глубины и цвета
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Очистка буфера глубины
	glClear( GL_DEPTH_BUFFER_BIT );
}

void core::reshape( uint16_t window_width, uint16_t window_height ) {
	// Установка положения и размера порта вывода
	glViewport( 0, 0, window_width, window_height );

	// Выбор матрицы проекции
	glMatrixMode( GL_PROJECTION );

	// Обнуление матрицы проекции
	glLoadIdentity( );

	// Определение матрицы наблюдения перспективной проекции:
	// Угол обзора по оси Y
	// Соотношение сторон экрана
	// Ближняя плоскость усеченной пирамиды наблюдения
	// Дальняя плоскость усеченной пирамиды наблюдения
	gluPerspective( 70.0f, ( ( float ) window_width / ( float )window_height ), 1.0f, 250.0f );

	// Выбор матрицы наблюдения моделей
	glMatrixMode( GL_MODELVIEW );

	// Обнуление матрицы
	glLoadIdentity( );
}

void fog::set( float start, float end, float density ) {
	// Enable fog
	// core::get_instance( ).enable( core::FOG );

	//Начало
	glFogf( GL_FOG_START, ( GLfloat )start);

	//Конец
	glFogf( GL_FOG_END, ( GLfloat )end );

	//Плотность
	glFogf( GL_FOG_DENSITY,( GLfloat ) density );
}

} //namespace demonblade
