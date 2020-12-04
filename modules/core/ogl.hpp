#ifndef OGL_HPP_INCLUDED
#define OGL_HPP_INCLUDED

/*
    ����� ��� ����������� ������ ������ � OpenGL ������ demonblade
    ��������� ����� - �������� ��� ������ � ��������� ��������� OpenGL

    �������������:
    db::ogl::get_instance( )-><method>( );
*/

#include <cstdint>
#include "../common/global.hpp"

// todo: light

namespace demonblade {

	class ogl {
		public:
			// ������������ ������� ����
			enum func_e {
				TEXTURE_1D			=	0x0DE0,	// �������� �� ���������� ���������
				TEXTURE_2D			=	0x0DE1,
				TEXTURE_3D			=	0x806F,
				TEXTURE_CUBE_MAP	=	0x8513,	// ���������� ��������
				LIGHT				=	0x0B50,	// ����
				ALPHA_TEST			=	0x0BC0,	// ����� ���� ( �������, �������� )
				FOG					=	0x0B60,	// �����
				CULL				=	0x0B44,	// ��������� ��������� ������
				DITHERING			=	0x0BD0	// ���������� ������ ��� ���������
				                        // todo GL_TEXTURE_CUBEMAP_SEAMLESS
				                        // todo DEPTH MASK
			};

			static ogl* get_instance( void ) {
				static ogl ogl_instance;	// lazy :<
				return &ogl_instance;
			}

			// ������� ������������� ���� OpenGL
			// ���������� true, ���� �������
			bool init( void );

			// ������� ������� ������� MODELVIEW � ������� OpenGL
			void clear( void );

			// ������� ��������� / ���������� ������������ OpenGL
			void enable( func_e type );
			void disable( func_e type );
			void select( func_e type, bool state );

		private:
			// ������ ������������, �����������, �������� �����������
			ogl( void ) { };
			~ogl( void ) { };
			ogl( const ogl &_ex ) = delete;
			ogl& operator=( const ogl& ) = delete;
	};	// ogl

	namespace fog {
		// ��������� ���������� ������
		// ������, �����, ���������
		void set( float start, float end, float density );

	}	// namespace fog

	namespace light {
		// todo
	}	// namespace light

} // namespace demonblade

#endif // OGL_HPP_INCLUDED
