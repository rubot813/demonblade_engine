#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "demonblade.hpp"	// Так подключается движок

/*
	Класс для тестов с движком demonblade.
	Здесь все сделано криво и косо, класс предназначен только для проверки
*/

class playground {
	public:
		playground( void );
		~playground( void );

		// ====
		// Главные методы
		bool init( void );		// Инициализация
		void update( void );	// Обновление логики
		void render( void );	// Отрисовка
		// ====

		// ====
		// Остальные методы
		// Метод считает и выдает FPS. Вызывать каждый кадр, меняет значение раз в секунду
		uint16_t calculate_frame_rate( void );

		// Метод отрисовки текста
		void render_text( sf::Vector2f position, std::string text );

		// ====
		// Переменные

		// Размеры окна
		const uint16_t window_size_x = 800;
		const uint16_t window_size_y = 600;

		// ====
		// Переменные SFML, начинаются с sf_

		// Основные переменные SFML
		sf::Event			sf_event;
		sf::RenderWindow	sf_render_window;
		sf::ContextSettings sf_context_settings;

		// Часы для расчета dt ( delta time. google it )
		sf::Clock sf_dt_clock;

		// Для отрисовки текста
		sf::Text sf_text;
		sf::Font sf_font;

		// Для загрузки картинок и передачи в db
		sf::Image sf_image;

		sf::Vector2i sf_mouse_offset;

		// ====
		// Переменные движка, начинаются с db_
		db::camera db_camera;
		db::texture db_texture;
		db::mesh	db_mesh;
		db::model	db_model;
};	// playground class

#endif // PLAYGROUND_H
