#ifndef TGA_HPP_INCLUDED
#define TGA_HPP_INCLUDED

#include <fstream>

#include "image.hpp"

/*
	����� ��������� �������� � tga �������
	������� image
*/

namespace demonblade {
	class tga : public image {

			// default
			tga( void );
			tga( std::string file_name );
			~tga( void );

			// ����� �������� ����������� �� �����
			bool load_from_file( std::string file_name );

			// ����� ������ ����������� � ����
			bool save_to_file( std::string file_name );

	};	// class tga

}	// namespace demonblade

#endif // TGA_HPP_INCLUDED
