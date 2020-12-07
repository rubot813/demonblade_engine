#include "ogl.hpp"
#include "../common/db_gl.hpp"

namespace demonblade {

	bool ogl::init( void  ) {

		// ������������� GLEW � ��������� ������
		GLenum glew_init_error = glewInit( );

		if ( glew_init_error != GLEW_OK ) {
			db_dbg_error( "init GLEW error\n" );
			return 0;
		}

		// ������� ��������� OpenGL

		// ��������� ����� ������� ����� ������ � RGBA
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

		// ��������� ������� �������
		glClearDepth( 1.0f );

		// ��������� ����� �������
		glEnable( GL_DEPTH_TEST );

		// ������� ����� �������: ������ ����� ������������ ������ ���� �� ����� � ������
		glDepthFunc( GL_LESS );

		// ��������� ��������� ��������� ������
		//glEnable( GL_CULL_FACE );

		// �������������� �������������� ���� �������� � ���������
		//glEnable( GL_NORMALIZE );
		//glEnable( GL_RESCALE_NORMAL );

		// ��������� ������� ����� �����
		glAlphaFunc( GL_GREATER, 0 );

		// ����� ������� ���������� �������
		// ����� �� �����, ���� ������� ������
		glMatrixMode( GL_MODELVIEW );

		db_dbg_msg( "init ok\n" );

		return 1;
	}

	void ogl::enable( func_e type ) {
		glEnable( type );
	}

	void ogl::disable( func_e type ) {
		glDisable( type );
	}

	void ogl::select( func_e type, bool state ) {
		state ? glEnable( type ) : glDisable( type );
	}

	void ogl::clear( void ) {
		// ������� ������ ������� � �����
		//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		// ������� ������ �������
		glClear( GL_DEPTH_BUFFER_BIT );
	}

	void fog::set( float start, float end, float density ) {
		// Enable fog
		// ogl::get_instance( ).enable( ogl::FOG );

		//������
		glFogf( GL_FOG_START, ( GLfloat )start);

		//�����
		glFogf( GL_FOG_END, ( GLfloat )end );

		//���������
		glFogf( GL_FOG_DENSITY, ( GLfloat ) density );
	}

} //namespace demonblade
