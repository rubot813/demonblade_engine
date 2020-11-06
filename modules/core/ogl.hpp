#ifndef OGL_HPP_INCLUDED
#define OGL_HPP_INCLUDED

/*
    ����� ��� ����������� ������ ������ � OpenGL ������ demonblade
    ��������� ����� - �������� ��� ������ � ��������� ��������� OpenGL
*/


#include <cstdint>

// todo: light

namespace demonblade {

	class ogl {
		public:
			static ogl* get_instance( void ) {
				static ogl ogl_instance;	// lazy :<
				return &ogl_instance;
			}

			// ������������ ������� ����
			enum func_e {
				TEXTURE_2D	= 0x0DE1,	// �������� 2D
				LIGHT		= 0x0B50,	// ����
				ALPHA_TEST	= 0x0BC0,	// ����� ���� ( �������, �������� )
				FOG			= 0x0B60,	// �����
				CULL		= 0x0B44,	// ��������� ��������� ������
				DITHERING	= 0x0BD0	// ���������� ������ ��� ���������
			};

			// ������� ������������� ���� OpenGL
			// ��������� ������� ����� ������ ( ���� ) ��� ����������� � ���� ������ ( FOV )
			bool init( uint16_t viewport_width, uint16_t viewport_height, float fov );

			// ������� ��������� �������� ����� ������
			void reshape( uint16_t new_viewport_width, uint16_t new_viewport_height );

			// ������ ��������� �������� ����� ������ � ���� ������	todo: refact after add camera
			inline uint16_t get_viewport_height( void );
			inline uint16_t get_viewport_width( void );
			inline uint16_t get_fov( void );

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

			// ������� ��������� �������� ����� ������
			// ����� ��������� �� private ����������
			void reshape( void );

			// ��������� ����
			// �������
			uint16_t _viewport_width, _viewport_height;

			// ���� ������ �� ��� Y
			float _fov;

		protected:
			// no childs allowed
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
