#ifndef OBJ_HPP_INCLUDED
#define OBJ_HPP_INCLUDED

#include "../render/mesh.hpp"

#include <sstream>
#include <fstream>

/*
	Класс позволяет работать с моделями формата OBJ Wavefront
	Основан на классе mesh
*/

namespace demonblade {

	class obj : public mesh {

		public:
			obj( void );
			~obj( void );

			// Метод загрузки модели из файла
			bool load_from_file( std::string file_name );

			// Метод записи модели в файл
			bool save_to_file( std::string file_name );

		private:

			// Структура индексов одного полигона
			typedef struct {
				glm::uvec3 vertex;
				glm::uvec3 texel;
				glm::uvec3 normal;
			} _polygon_index_s;

	};	// obj class

}	// namespace demonblade

#endif // OBJ_HPP_INCLUDED
