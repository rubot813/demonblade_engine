#include "playground.h"

playground::playground( void ) {
	// �������������
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
					// ��� ����� �������� ������ ����� ������ ������ ��� ��������� �������� ������
					db_camera.set_viewport( sf_render_window.getSize( ).x,
					                        sf_render_window.getSize( ).y, 60.0f );

				default:
					break;
			}	// event switch
		} // while poll events

		// ���������� ������
		update( );

		// ���������
		render( );

	}	// while window is opened
}	// constructor

playground::~playground( void ) {

}

bool playground::init( void ) {
	bool _init = 1;

	// ====
	// �������� � ��������� ������, ��������� ������
	if ( !sf_font.loadFromFile( "resources/FSEX300.ttf" ) )
		_init = 0;
	sf_text.setFont( sf_font );
	sf_text.setCharacterSize( 15 );
	sf_text.setFillColor( sf::Color::White );

	// ====
	// ��������� ��������� OpenGL
	// ��� ��������� ����� ��������� � ��������,
	// �� �������� ��� ��� ����� ����������� ���.
	// �������� ������ OpenGL ����� ���� 3.0, ���� 3.2 ��� 3.3 �� ��������������

	// ������ ������ OpenGL 3.3
	sf_context_settings.minorVersion = 3;
	sf_context_settings.majorVersion = 3;

	// ���������� ��� �� ������� � ������ �������
	sf_context_settings.depthBits = 24;

	// ���������� ��� �� ������� � ������ ��������� ( � ������ ������ ������ ��� �� ���������� )
	sf_context_settings.stencilBits = 8;

	// ������� ��������������� ( ����������� )
	sf_context_settings.antialiasingLevel = 0;

	// ====
	// �������� � ��������� ����
	sf_render_window.create( sf::VideoMode( window_size_x, window_size_y ), "Demonblade engine v" + std::to_string( DB_VERSION ), sf::Style::Default, sf_context_settings );
	sf_render_window.setVerticalSyncEnabled( 0 );	// ���� ������������ �������������
	sf_render_window.setFramerateLimit( 60 );		// ��������� ����������� ������
	sf_render_window.setMouseCursorVisible( 1 );	// ���������� ��������� ������� � ����

	// ����� ������������� ��������� OpenGL
	sf_context_settings = sf_render_window.getSettings( );

	// ��������� ������� ���� �������� ��� ��������� ����� OpenGL
	sf_render_window.setActive( 1 );

	// ������������� DB

	// ������������� GLEW, ������� ������ � �������
	if ( !db::ogl::get_instance( )->init( ) )
		_init = 0;

	db::ogl::get_instance( )->enable( db::ogl::TEXTURE_2D );
	db::ogl::get_instance( )->enable( db::ogl::TEXTURE_CUBE_MAP );

	// ��������� ������ ( ��� �����������,���� ���� ����� �������� )
	// ����������� � ������������� ������� ������������� ��������
	db_camera.set_viewport( window_size_x, window_size_y, 60.0f );
	db_camera.set_center( { 0.0f, 0.0f, -1.0f });
	db_camera.set_position( { 0.0f, 0.0f, 0.0f });

	if ( db_bmp.load_from_file( "resources/uCar3.bmp" ) )
		std::cout << "Load tex done!\n";

	if ( db_texture.load_from_image( &db_bmp ) )
		std::cout << "Load texture ok!\n";

	if ( db_mesh.load_from_file( "resources/box.obj" ) )
		std::cout << "Load mesh ok!\n";

	if ( db_model.set_data( &db_mesh, &db_texture ) )
		std::cout << "Model set data ok!\n";

	if ( db_sprite.set_data( db::sprite::SPHERICAL, glm::vec2( 0.2f, 0.2f ), &db_texture ) ) {
		std::cout << "Sprite add tex ok!\n";
	}

	db_model.set_position( glm::vec3( 1.0f, -.5f, -2.0f ) );

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

	if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) ) {
		// ������ ������ �������� ����� ������������ ������ ����
		sf_mouse_offset = sf::Mouse::getPosition( sf_render_window ) - sf::Vector2i( sf_render_window.getSize( ).x / 2.0f,
		                  sf_render_window.getSize( ).y / 2.0f );

		// ������������ ��������� ������� �� ������ ����
		sf::Mouse::setPosition( sf::Vector2i( sf_render_window.getSize( ).x / 2.0f, sf_render_window.getSize( ).y / 2.0f ), sf_render_window );

		// x - yaw, y - pitch
		// ������������ ���� �������� ������ � �����������������
		glm::vec2 _tmp;
		_tmp.x = sf_mouse_offset.x;	// sf::Vector2f -> glm::vec2
		_tmp.y = -sf_mouse_offset.y;
		glm::vec2 angle = _tmp * mouse_sens;

		// �������� �������� ��������� ���� �� ������ � ���� �������� ������
		db_camera.add_angle( angle );

		// ����������� �������� ������ �� ��� y
		db_camera.constraint_pitch( );

		// ������ ����� ���� �������� ������ �� �������� �����
		db_camera.calc_center( );
	}
}

void playground::render( void ) {
	// ====
	// ������� ���������:
	// 1. �������� ����� ���� �� SFML ( ������� clear )
	// 2. �������� ������� db ( ������� clear )
	// 3. ���������� ������ db
	// 4. ��������� �� db
	// 5. ��������� ��������� OpenGL � ���� ( ������� pushGLStates )
	// 6. �������� �� SFML ������ ������������� ������� ( GUI / HUD etc. )
	// 7. ������� ��������� OpenGL �� ����� ( ������� popGLStates )
	// 8. ���������� ��� �� ����� ����� SFML display
	// ====


	// 1
	sf_render_window.clear( sf::Color::Black );

	// 2
	db::ogl::get_instance( )->clear( );

	// 3
	// ���������� ����� �� ������ db_camera
	db_camera.view( );

	// 4. ����� ��� ��������� ������ ��� ������� OpenGL ���
	// ====

	db_model.render( );

	db_sprite.render( );

	// ====
	// 5
	sf_render_window.pushGLStates( );

	// 6
	// ====
	// ����� ��� ��������� SFML ( sfml draw ������ )


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
