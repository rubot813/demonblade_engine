#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "demonblade.hpp"	// Так подключается движок

// rem after tests
#ifndef GLEW_STATIC
	#define GLEW_STATIC	// important, before including glew
#endif	// GLEW_STAIC
#include <glew/include/GL/glew.h>	//	defines glext, glew

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
		const uint16_t window_size_x = 1280;
		const uint16_t window_size_y = 720;
		const float window_fov		 = 60.0f;
		const float camera_speed	 = 0.05f;
		const float mouse_sens		 = 0.00005f;

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
		db::fp_camera	db_camera;
		db::texture_2d db_texture;
		db::obj		db_obj;
		db::model	db_model;
		db::sprite	db_sprite;
		db::bmp		db_bmp;

};	// playground class

#endif // PLAYGROUND_H
