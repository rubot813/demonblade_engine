#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "../common/gl_libs.hpp"
#include "texture.hpp"
#include "mesh.hpp"

#include <sstream>
#include <fstream>
#include <vector>

/*
	Класс, позволяющий универсально работать с моделями разных форматов
	Важно! Интенсивно работает с память, смотри использование:

	Использование:
	// ====
	db::texture tex;
    db::mesh mesh;
    db::model *m
    m = new db::model( &mesh, &tex );
    ...
    delete m;	// Здесь он не сломает tex и mesh
    // ====

    db::model m( new db::mesh( ... ), new db::texture( ... ) );

    // ====

    db::texture tex;
    db::mesh mesh;

    db::model m;
    m.set_texture( &tex )
    m.set_mesh( &mesh )

	// ====
*/

// todo: render from container
// todo: i_drawable

namespace demonblade {
	// Класс описывает одну модель
	class model {

		public:
			// Пустой конструктор по умолчанию
			model( void );

			// Конструктор с указателями на заранее загруженный меш и загруженную текстуру
			model( mesh *msh, texture *tex );

			// Конструктор с созданием экземпляра текстуры и экземпляра меша
			model( mesh msh, texture tex );

			~model( void );

			// Метод установки текстуры для модели и меша модели
			// Вернут true в случае успеха
			bool set_texture( texture *tex );
			bool set_mesh( mesh *msh );

			// Методы получения указателей на текстуру и меш модели
			texture*	get_texture( void );
			mesh*		get_mesh( void );

			// Методы перемещения, вращения и масштабирования модели
			void move( glm::vec3 offset );
			void rotate( glm::vec3 offset );
			void scale( glm::vec3 offset );

			// Методы установки позиции, поворота и масштаба модели
			void set_position( glm::vec3 value );
			void set_rotation( glm::vec3 value );
			void set_scale( glm::vec3 value );

			// Методы получения позиции, поворота и масштаба модели
			glm::vec3 get_position( void );
			glm::vec3 get_rotation( void );
			glm::vec3 get_scale( void );

			// Метод отрисовки модели
			void render( void );

		private:

			// Базовые параметры модели: положение, вращение и масштабирование
			glm::vec3 _position;
			glm::vec3 _rotation;
			glm::vec3 _scale;

			// Световые параметры модели
			glm::vec4 _ambient;		// Рассеянный свет
			glm::vec4 _diffuse;		// Диффузный свет
			glm::vec4 _specular;	// Отраженный свет

			// Указатель на загруженную текстуру в VRAM
			texture::texture_t	*_texture_vram;

			// Указатель на экземпляр класса текстур
			texture				*_texture;

			// Указатель на экземпляр класса работы с мешем
			mesh				*_mesh;

			// Флаги, что мы создавали экземпляр меша или текстуры
			// Используются в декструкторе чтобы освободить память
			bool _mesh_allocated;
			bool _tex_allocated;

	};	// class model

}	// namespace demonblade

#endif // MODEL_HPP_INCLUDED
