#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <cstdint>	// C++11
#ifndef __GNUC__	// For VC
	#include <cstddef>
#endif
#include "../core/ogl.hpp"

/*
	����� texture ��������� ������� ������ ��������
*/

namespace demonblade {

	class texture {

		public:

			// ����� ��������, ����� �� ������� GLuint
			typedef std::size_t texture_id;

			// ����� ��������� ��������
			void bind( void );

			// ����� ��������� ���������� ���������� ���������
			virtual uint8_t get_tex_coords_num( void );

			// ����� ��������� ��������� �� ������������� ���������� ��������
			texture_id* get_pointer( void );

		protected:

			// ������������� ����������� ��������
			texture_id	_texture_ptr;

			// ��� ��������
			std::size_t	_type;

	};	// class texture

}	// namespace demonblade
#endif // TEXTURE_HPP_INCLUDED
