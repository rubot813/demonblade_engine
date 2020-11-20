#ifndef SPRITE_HPP_INCLUDED
#define SPRITE_HPP_INCLUDED

#include "drawable.hpp"
#include "texture.hpp"
/*
	�����, ����������� �������� �� ��������� - ������������ ���������,
	������� ������ ��������� � ������
*/

namespace demonblade {
	// ����� ��������� ���� ������
	class sprite : public drawable {

		public:

			// ���� ��������
			typedef enum {
				// �����������: ������ ��������� � ������
				SPHERICAL,

				// �������������: ��������� � ������ �� ��� x
				CYLINDRICAL

			} type_e;

			sprite( void );
			~sprite( void );

			// ����� ��������� ������ �������
			// ���������� 1 ���� ��� �������
			bool set_data( type_e type, glm::vec2 size, texture *tex_ptr );


			// ������ ��������� � ��������� ���� �������
			void set_type( type_e type );
			type_e get_type( void );

			// ������ ��������� � ��������� ������� �������
			void set_size( glm::vec2 size );
			glm::vec2 get_size( void );


			// ������ ��������� � ��������� ��������
			bool set_texture( texture *tex_ptr );
			texture*	get_texture( void );


			// ����� ���������
			void render( void );	// virtual

		private:

			// ������
			glm::vec2			_size;

			// ���
			type_e				_type;

			// ������� � ���������� ����������
			glm::vec3			_vertex[ 6 ];
			glm::vec2			_texel[ 6 ];

			// �������� � ��� ��������
			texture				*_texture;
			texture::texture_t	*_texture_name;

	};	// class sprite

}	// namespace demonblade

#endif // SPRITE_HPP_INCLUDED
