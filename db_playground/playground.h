#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "demonblade.hpp"	// ��� ������������ ������

// rem after tests
#ifndef GLEW_STATIC
	#define GLEW_STATIC	// important, before including glew
#endif	// GLEW_STAIC
#include <glew/include/GL/glew.h>	//	defines glext, glew

/*
	����� ��� ������ � ������� demonblade.
	����� ��� ������� ����� � ����, ����� ������������ ������ ��� ��������

*/

class playground {
	public:
		playground( void );
		~playground( void );

		// ====
		// ������� ������
		bool init( void );		// �������������
		void update( void );	// ���������� ������
		void render( void );	// ���������
		// ====

		// ====
		// ��������� ������
		// ����� ������� � ������ FPS. �������� ������ ����, ������ �������� ��� � �������
		uint16_t calculate_frame_rate( void );

		// ����� ��������� ������
		void render_text( sf::Vector2f position, std::string text );

		// ====
		// ����������

		// ������� ����
		const uint16_t window_size_x = 1280;
		const uint16_t window_size_y = 720;
		const float window_fov		 = 60.0f;
		const float camera_speed	 = 0.05f;
		const float mouse_sens		 = 0.00005f;

		// ====
		// ���������� SFML, ���������� � sf_

		// �������� ���������� SFML
		sf::Event			sf_event;
		sf::RenderWindow	sf_render_window;
		sf::ContextSettings sf_context_settings;

		// ���� ��� ������� dt ( delta time. google it )
		sf::Clock sf_dt_clock;

		// ��� ��������� ������
		sf::Text sf_text;
		sf::Font sf_font;

		// ��� �������� �������� � �������� � db
		sf::Image sf_image;

		sf::Vector2i sf_mouse_offset;

		// ====
		// ���������� ������, ���������� � db_
		db::fp_camera	db_camera;
		db::texture_2d db_texture;
		db::obj		db_obj;
		db::model	db_model;
		db::sprite	db_sprite;
		db::bmp		db_bmp;

};	// playground class

#endif // PLAYGROUND_H
