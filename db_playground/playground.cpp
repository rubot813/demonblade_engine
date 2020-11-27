#include "playground.h"


float skyboxVertices[] = {
	// Координаты
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};

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

				case sf::Event::Resized:
					// Так можно изменить размер порта вывода движка при изменении размеров экрана
					db_camera.set_viewport( sf_render_window.getSize( ).x,
					                        sf_render_window.getSize( ).y, 60.0f );

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
	sf_render_window.create( sf::VideoMode( window_size_x, window_size_y ), "Demonblade engine v" + std::to_string( DB_VERSION ), sf::Style::Default, sf_context_settings );
	sf_render_window.setVerticalSyncEnabled( 0 );	// Откл вертикальной синхронизации
	sf_render_window.setFramerateLimit( 60 );		// Установка ограничения кадров
	sf_render_window.setMouseCursorVisible( 1 );	// Отключение видимости курсора в окне

	// Берем установленные настройки OpenGL
	sf_context_settings = sf_render_window.getSettings( );

	// Установка данного окна активным для отрисовки через OpenGL
	sf_render_window.setActive( 1 );

	// Инициализация DB

	// Инициализация GLEW, очистка матриц и буферов
	if ( !db::ogl::get_instance( )->init( ) )
		_init = 0;
	db::ogl::get_instance( )->enable( db::ogl::TEXTURE_2D );
	db::ogl::get_instance( )->enable( db::ogl::TEXTURE_CUBE_MAP );

	// Настройка камеры ( она обязательна,даже если будет статична )
	// Настраивает и устанавливает матрицу перспективной проекции
	db_camera.set_viewport( window_size_x, window_size_y, 60.0f );
	db_camera.set_center( { 0.0f, 0.0f, -1.0f });
	db_camera.set_position( { 0.0f, 0.0f, 0.0f });

	sf_image.loadFromFile( "resources/box.jpg" );
	if ( db_texture.load_from_memory( sf_image.getPixelsPtr( ),
	                                  sf_image.getSize( ).x,
	                                  sf_image.getSize( ).y ) )
		std::cout << "Load texture ok!\n";

	if ( db_mesh.load_from_file( "resources/box.obj" ) )
		std::cout << "Load mesh ok!\n";

	if ( db_model.set_data( &db_mesh, &db_texture ) )
		std::cout << "Model add part ok!\n";

	if ( db_sprite.set_data( db::sprite::SPHERICAL, glm::vec2( 0.2f, 0.2f ), &db_texture ) ) {
		std::cout << "Sprite add tex ok!\n";
	}

	if ( db_sb_mesh.load_from_file( "resources/box.obj" ) )
		std::cout << "Load mesh sb ok!\n";

	db_model.set_position( glm::vec3( 1.0f, -.5f, -2.0f ) );

	if ( !sf_image_cm[ 0 ].loadFromFile( "resources/clouds1_down.bmp" ) )
		std::cout << "ERR 0";
	if ( !sf_image_cm[ 1 ].loadFromFile( "resources/clouds1_east.bmp" ) )
		std::cout << "ERR 1";
	if ( !sf_image_cm[ 2 ].loadFromFile( "resources/clouds1_north.bmp" ) )
		std::cout << "ERR 2";
	if ( !sf_image_cm[ 3 ].loadFromFile( "resources/clouds1_south.bmp" ) )
		std::cout << "ERR 3";
	if ( !sf_image_cm[ 4 ].loadFromFile( "resources/clouds1_up.bmp" ) )
		std::cout << "ERR 4";
	if ( !sf_image_cm[ 5 ].loadFromFile( "resources/clouds1_west.bmp" ) )
		std::cout << "ERR 5";

	uint16_t w = sf_image_cm[ 0 ].getSize( ).x;
	uint16_t h = sf_image_cm[ 0 ].getSize( ).y;
	for ( uint8_t i = 0; i < 6; i++ ) {
		cm_ptrs[ i ] = const_cast< void* >( reinterpret_cast< const void *>( sf_image_cm[ i ].getPixelsPtr( ) ) );
		if ( cm_ptrs[ i ] == nullptr )
			std::cout << "FCK";
		std::cout << "MEMVAL = " << &cm_ptrs[ i ] << "\n";
	}
	if ( db_texture_cm.load_from_memory( cm_ptrs, w, h ) )
		std::cout << "DONE";

	// ====

	return _init;
}

void playground::update( void ) {
	db_model.rotate( { .0f, -.1f, .0f } );

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
		db_camera.move_forward( camera_speed );

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
		db_camera.move_backward( camera_speed );

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
		db_camera.move_left( camera_speed );

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
		db_camera.move_right( camera_speed );

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
		db_camera.move_up( camera_speed );

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::LShift ) )
		db_camera.move_down( camera_speed );

	// Считаю вектор смещения курса относительно центра окна
	sf_mouse_offset = sf::Mouse::getPosition( sf_render_window ) - sf::Vector2i( sf_render_window.getSize( ).x / 2.0f,
	                  sf_render_window.getSize( ).y / 2.0f );

	// Устанавливаю положение курсора по центру окна
	sf::Mouse::setPosition( sf::Vector2i( sf_render_window.getSize( ).x / 2.0f, sf_render_window.getSize( ).y / 2.0f ), sf_render_window );

	// x - yaw, y - pitch
	// Пересчитываю углы поворота камеры с чувствительностью
	glm::vec2 _tmp;
	_tmp.x = sf_mouse_offset.x;	// sf::Vector2f -> glm::vec2
	_tmp.y = -sf_mouse_offset.y;
	glm::vec2 angle = _tmp * mouse_sens;

	// Добавляю смещение указателя мыши от центра к углу поворота камеры
	db_camera.add_angle( angle );

	// Ограничение поворота камеры по оси y
	db_camera.constraint_pitch( );

	// Считаю новый угол поворота камеры по заданным углам
	db_camera.calc_center( );
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

	// 3
	// Проецируем сцену от камеры db_camera
	db_camera.view( );

	// 4. Здесь вся отрисовка движка или обычный OpenGL код
	// ====

	//db_model.render( );

	//db_sprite.render( );

	// ====
	// Сохранение текущего состояния трансформации матрицы modelview в стек
	glPushMatrix( );
	// Установка текстуры для отрисовки
	db_texture_cm.bind( );
	// Включение режима вершинных массивов
	glEnableClientState( GL_VERTEX_ARRAY );
	// Включение режима массивов текстурных координат
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	// Создание указателя на массив вершин
	// количество координат,
	// тип данных,
	// смещение данных в массиве
	// указатель на массив
	glVertexPointer( 3, GL_FLOAT, 0, db_sb_mesh.get_vertex_ptr( )->data( ) );
	// Создание указателя на массив текстурных координат
	// количество координат,
	// тип данных,
	// смещение данных в массиве
	// указатель на массив
	glTexCoordPointer( 2/* # */, GL_FLOAT, 0, db_sb_mesh.get_texel_ptr( )->data( ) );
	// Отрисовка массива
	// Тип данных для отрисовки
	// начальный индекс массива
	// количество элементов для отрисовки
	glDrawArrays( GL_TRIANGLES, 0, db_sb_mesh.get_vertex_ptr( )->size( ) );
	// Выключение режима массивов текстурных координат
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	// Выключение режима вершинных массивов
	glDisableClientState( GL_VERTEX_ARRAY );
	// Восстановление состояния матрицы modelview из стека
	glPopMatrix( );


	// ====

	// ====
	// 5
	sf_render_window.pushGLStates( );

	// 6
	// ====
	// Здесь вся отрисовка SFML ( sfml draw методы )


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
