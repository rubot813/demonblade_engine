#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "./glm/glm.hpp"
#include "texture.hpp"
#include <sstream>
#include <fstream>
#include <vector>

// todo: render from container
// todo: i_drawable

namespace demonblade {
	// Класс описывает одну модель
	class model {

public:
	// Пустой конструктор по умолчанию
	model( void );

	// Метод загрузки массивов вершин, текселей и нормалей из Wavefront OBJ файла
	// Вернет true в случае успеха
	bool load_from_obj( std::string file_name );

	// Метод установки текстуры для модели
	// Вернет true в случае успеха
	bool set_texture( texture::texture_t *tex );

	// Методы перемещения, вращения и масштабирования модели
	inline void move( glm::vec3 offset );
	inline void rotate( glm::vec3 offset );
	inline void scale( glm::vec3 offset );

	// Методы установки позиции, поворота и масштаба модели
	inline void set_position( glm::vec3 value );
	inline void set_rotation( glm::vec3 value );
	inline void set_scale( glm::vec3 value );

	// Метод отрисовки модели
	void render( void );

	// types, methods
	private:
		// Структура индексов одной поверхности ( треугольника )
		typedef struct {
			// Индексы вершин, текселей и нормалей
			glm::uvec3 vertex;
			glm::uvec3 texel;
			glm::uvec3 normal;
		} _face_ind_s;

		// Базовые параметры модели: положение, вращение и масштабирование
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;

		// Световые параметры модели
		glm::vec4 _ambient;		// Рассеянный свет
		glm::vec4 _diffuse;		// Диффузный свет
		glm::vec4 _specular;	// Отраженный свет

		// Вершины модели
		std::vector< glm::vec3 > _vertex;

		// Тексели ( текстурные координаты ) модели
		std::vector< glm::vec2 > _texel;

		// Нормали модели
		std::vector< glm::vec3 > _normal;

		// Текстура модели
		texture::texture_t *_texture;

	};	// class model

}	// namespace demonblade

#endif // MODEL_HPP_INCLUDED
