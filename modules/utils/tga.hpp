#ifndef TGA_HPP_INCLUDED
#define TGA_HPP_INCLUDED

#include <fstream>

#include "image.hpp"

/*
	Класс позволяет работать с tga файлами
	Потомок image
*/

namespace demonblade {
	class tga : public image {

			// default
			tga( void );
			tga( std::string file_name );
			~tga( void );

			// Метод загрузки изображения из файла
			bool load_from_file( std::string file_name );

			// Метод записи изображения в файл
			bool save_to_file( std::string file_name );

	};	// class tga

}	// namespace demonblade

#endif // TGA_HPP_INCLUDED
