#ifndef MESH_HPP_INCLUDED
#define MESH_HPP_INCLUDED

#include "../common/db_glm.hpp"
#include "../common/global.hpp"
#include <vector>

/*
	Базовый класс для меша ( полигональной сетки ) модели.
	Поддерживаемые форматы: Wavefront OBJ
	todo: milkshape 3d, md2 with anim
*/

namespace demonblade {

	class mesh {

		public:
			mesh( void );
			~mesh( void );
			void operator=( mesh &m );

			// Метод загрузки модели из файла
			virtual bool load_from_file( std::string file_name ) = 0;

			// Метод записи модели в файл
			virtual bool save_to_file( std::string file_name ) = 0;

			// Метод возвращает указатель на контейнер с координатами вершин
			std::vector< glm::vec3 >* get_vertex_ptr( void );

			// Метод возвращает указатель на контейнер с текстурными координатами
			std::vector< glm::vec2 >* get_texel_ptr( void );

			// Метод возвращает указатель на контейнер с нормалями
			std::vector< glm::vec3 >* get_normal_ptr( void );

		protected:

			// Вершины
			std::vector< glm::vec3 > _vertex;

			// Тексели ( текстурные координаты )
			std::vector< glm::vec2 > _texel;

			// Нормали
			std::vector< glm::vec3 > _normal;

	};	// mesh class

}	// namespace demonblade

#endif // MESH_HPP_INCLUDED
