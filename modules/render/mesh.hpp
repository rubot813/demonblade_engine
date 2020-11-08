#ifndef MESH_HPP_INCLUDED
#define MESH_HPP_INCLUDED

#include "../common/gl_libs.hpp"
#include <sstream>
#include <vector>

/*
	Класс описывает меш ( полигональную сетку ) модели
	позволяет загружать вершины, текстурные координаты и карты нормалей из файлов
	Поддерживаемые форматы: Wavefront OBJ
	todo: md2 with anim
*/

namespace demonblade {

	class mesh {

		public:
			// Пустой конструктор по умолчанию
			mesh( void );

			// Конструктор с загрузкой меша из файла
			// Результат можно получить через метод get_load_result
			mesh( std::string file_name );

			~mesh( void );

			// Форматы файла, из которого был загружен меш
			typedef enum {
				UNKNOWN		= 0,	// Неизвестный формат
				OBJ					// Wavefront OBJ
			} format_e;

			// Метод загрузки меша из файла, определяет формат автоматически
			// В случае успеха вернет true
			bool load_from_file( std::string file_name );

			// Принимает формат меша, игнорируя формат файла
			// В случае успеха вернет true
			bool load_from_file( std::string file_name, format_e format );

			// Метод возвращает формат файла, из которого был загружен меш
			format_e get_file_format( void );

			// Метод возвращает результат загрузки меша из файла
			// true - успешно загружен
			bool get_load_result( void );

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
			bool _load_obj( void );

			// Метод установки внутренних переменных
			// Принимает формат файла, флаг успеха загрузки, имя файла
			void _set_internal( format_e fm, bool fl, std::string *fn );

			// Метод очистки внутренних переменных
			void _clean_internal( void );

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

			// Имя файла, из которого был загружен меш
			std::string				_file_name;

			// Формат файла, из которого был загружен меш
			format_e				_format;

			// Флаг успешной загрузки меша
			bool					_succes_flag;
	};	// mesh class

}	// namespace demonblade

#endif // MESH_HPP_INCLUDED
