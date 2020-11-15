#include "playground.h"

playground::playground( void ) {
	// Инициализация
	if ( !init( ) )
		return;

	// Base SFML cycle
	while( sf_render_window.isOpen( ) ) {

		// Check events
		while( sf_render_window.pollEvent( sf_event ) ) {
			switch ( sf_event.type ) {

				case sf::Event::Closed:
					sf_render_window.close( );

				default:
					break;
			}	// event switch
		} // while poll events

		// Обновление логики
		update( );

		// Отрисовка
		render( );

	}	// while window is opened
}	// constructor

playground::~playground( void ) {

}

bool playground::init( void ) {
	bool _init = 1;

	// ====
	// Загрузка и установка шрифта, настройка текста
	if ( !sf_font.loadFromFile( "resources/FSEX300.ttf" ) )
		_init = 0;
	sf_text.setFont( sf_font );
	sf_text.setCharacterSize( 15 );
	sf_text.setFillColor( sf::Color::White );

	// ====
	// Настройка контекста OpenGL
	// Эти параметры будут запрошены у драйвера,
	// но гарантии что они будут установлены нет.
	// Например версия OpenGL может быть 3.0, если 3.2 или 3.3 не поддерживается

	// Запрос версии OpenGL 3.3
	sf_context_settings.minorVersion = 3;
	sf_context_settings.majorVersion = 3;

	// Количество бит на пиксель в буфере глубины
	sf_context_settings.depthBits = 24;

	// Количество бит на пиксель в буфере трафарета ( в данный момент движок его не использует )
	sf_context_settings.stencilBits = 8;

	// Уровень мультисэмплинга ( сглаживание )
	sf_context_settings.antialiasingLevel = 0;

	// ====
	// Создание и настройка окна
	sf_render_window.create( sf::VideoMode( window_size_x, window_size_y ), "Demonblade engine v" + std::to_string( DB_VERSION ) , sf::Style::Default, sf_context_settings );
	sf_render_window.setVerticalSyncEnabled( 0 );	// Откл вертикальной синхронизации
	sf_render_window.setFramerateLimit( 60 );		// Установка ограничения кадров
	// sf_render_window.setMouseCursorVisible( 0 );	// Отключение видимости курсора в окне

	// Берем установленные настройки OpenGL
	sf_context_settings = sf_render_window.getSettings( );

	// Установка данного окна активным для отрисовки через OpenGL
	sf_render_window.setActive( 1 );

	// Инициализация DB

	// Инициализация GLEW, очистка матриц и буферов
	if ( !db::ogl::get_instance( )->init( ) )
		_init = 0;
	db::ogl::get_instance( )->enable( db::ogl::TEXTURE_2D );

	// Настройка камеры ( она обязательна,даже если будет статична )
	// Настраивает и устанавливает матрицу перспективной проекции
	db_camera.set_viewport( window_size_x, window_size_y, 60.0f );
	db_camera.set_position( { 0.0f, 0.0f, -100.0f });

	sf_image.loadFromFile( "resources/grass_001.png" );
	if ( db_texture.load_from_memory( sf_image.getPixelsPtr( ),
								sf_image.getSize( ).x,
								sf_image.getSize( ).y ) )
			std::cout << "Load texture ok!\n";

	if ( db_mesh.load_from_file( "resources/box.obj" ) )
		std::cout << "Load mesh ok!\n";

	if ( db_model.add_part( &db_mesh, &db_texture ) )
		std::cout << "Model add part ok!\n";

	return _init;
}

void playground::update( void ) {
	//db_model.move( { 0.0f, 0.0f, 0.1f } );
	//db_model.set_position( glm::vec3{ 0.0f, 0.0f, 0.0f } );
}

void playground::render( void ) {
	// ====
	// Порядок отрисовки:
	// 1. Очистить буфер окна из SFML ( вызвать clear )
	// 2. Очистить матрицы db ( вызвать clear )
	// 3. Установить камеру db
	// 4. Отрисовка из db
	// 5. Поместить состояние OpenGL в стек ( вызвать pushGLStates )
	// 6. Рисовать из SFML поверх отрисованного движком ( GUI / HUD etc. )
	// 7. Вернуть состояние OpenGL из стека ( вызвать popGLStates )
	// 8. Отрисовать все на экран через SFML display
	// ====


	// 1
	sf_render_window.clear( sf::Color::Black );

	// 2
	db::ogl::get_instance( )->clear( );

	// 3, 4
	// Здесь вся отрисовка движка или обычный OpenGL код
	// ====

	// Проецируем сцену от камеры db_camera
	db_camera.project( );

	// Рисуем модельку
	db_model.render( );

	// ====
	// 5
	sf_render_window.pushGLStates( );

	// 6
	// ====
	// Здесь вся отрисовка SFML


	// ====
	// 7
	sf_render_window.popGLStates( );

	// 8
	sf_render_window.display( );
}

uint16_t playground::calculate_frame_rate( void ) {
	static sf::Clock sf_fps_clock;
	static uint16_t frame_counter = 0;
	static uint16_t calculated_fps = 0;
	frame_counter++;
	if ( sf_fps_clock.getElapsedTime( ).asSeconds( ) > 0 ) {
		calculated_fps = frame_counter;
		frame_counter = 0;
		sf_fps_clock.restart( );
	}
	return calculated_fps;
}

void playground::render_text( sf::Vector2f position, std::string text ) {
	sf_text.setPosition( position );
	sf_text.setString( text );
	sf_render_window.draw( sf_text );
}
