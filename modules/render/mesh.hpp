#ifndef MESH_HPP_INCLUDED
#define MESH_HPP_INCLUDED

#include "../common/db_glm.hpp"
#include "../common/global.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

/*
	Класс описывает меш ( полигональную сетку ) модели
	позволяет загружать вершины, текстурные координаты и карты нормалей из файлов
	Поддерживаемые форматы: Wavefront OBJ
	todo: milkshape 3d, md2 with anim
*/

namespace demonblade {

	class mesh {

		public:
			mesh( void );
			~mesh( void );
			void operator=( mesh &m );

			// Форматы файла, из которого может быть загружен меш
			typedef enum {
				UNKNOWN		= 0,	// Неизвестный формат
				OBJ					// Wavefront OBJ
			} format_e;

			// Метод загрузки меша из файла, определяет формат автоматически
			// В случае успеха вернет true
			bool load_from_file( std::string file_name );

			// Принимает формат меша с указанием формата файла
			// В случае успеха вернет true
			bool load_from_file( std::string file_name, format_e format );

			// Метод возвращает указатель на контейнер с координатами вершин
			std::vector< glm::vec3 >* get_vertex_ptr( void );

			// Метод возвращает указатель на контейнер с текстурными координатами
			std::vector< glm::vec2 >* get_texel_ptr( void );

			// Метод возвращает указатель на контейнер с нормалями
			std::vector< glm::vec3 >* get_normal_ptr( void );

		private:

			// Метод получения формата файла из пути к нему
			format_e _get_extension( std::string *path );

			// Метод загрузки меша из OBJ файла
			bool _load_obj( std::string fname );

			// types, methods
		private:
			// Структура индексов одной поверхности ( треугольника )
			typedef struct {
				// Индексы вершин, текселей и нормалей
				glm::uvec3 vertex;
				glm::uvec3 texel;
				glm::uvec3 normal;
			} _face_ind_s;

			// Вершины
			std::vector< glm::vec3 > _vertex;

			// Тексели ( текстурные координаты )
			std::vector< glm::vec2 > _texel;

			// Нормали
			std::vector< glm::vec3 > _normal;

	};	// mesh class

}	// namespace demonblade

#endif // MESH_HPP_INCLUDED
