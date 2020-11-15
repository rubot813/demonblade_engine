#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "demonblade.hpp"	// ��� ������������ ������

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
		const uint16_t window_size_x = 800;
		const uint16_t window_size_y = 600;

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
		db::camera db_camera;
		db::texture db_texture;
		db::mesh	db_mesh;
		db::model	db_model;
};	// playground class

#endif // PLAYGROUND_H
