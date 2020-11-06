#include "ogl.hpp"
#include "../common/gl_libs.hpp"

namespace demonblade {

	bool ogl::init( uint16_t viewport_width, uint16_t viewport_height, float fov ) {

		// ������������� GLEW � ��������� ������
		GLenum glew_init_error = glewInit( );

		if ( glew_init_error != GLEW_OK )
			return 0;

		// ������������� OpenGL

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

		// Save vport params
		_viewport_height	= viewport_height;
		_viewport_width		= viewport_width;
		_fov				= fov;

		// ��������� �������� ����� ������
		reshape( );

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

	void ogl::reshape(  uint16_t new_viewport_width, uint16_t new_viewport_height ) {
		// Save vport params
		_viewport_height	= new_viewport_height;
		_viewport_width		= new_viewport_width;

		reshape( );
	}

	void ogl::reshape( void ) {
		// ��������� ��������� � ������� ����� ������
		glViewport( 0, 0, _viewport_width, _viewport_height );

		// ����� ������� ��������
		glMatrixMode( GL_PROJECTION );

		// ��������� ������� ��������
		glLoadIdentity( );

		// ������ ����������� ������ ������
		float aspect_ratio = ( ( float )_viewport_width / ( float )_viewport_height );

		// ����������� ������� ���������� ������������� �������� ( GL_PROJECTION ):
		// ���� ������ �� ��� Y
		// ����������� ������ ������
		// ������� ��������� ��������� �������� ����������
		// ������� ��������� ��������� �������� ����������
		glm::mat4 projection_mat = glm::perspective( _fov, aspect_ratio, 1.0f, 250.0f );	// todo: magic nums?
		glLoadMatrixf( glm::value_ptr( projection_mat ) );

		// ����� ������� ���������� �������
		glMatrixMode( GL_MODELVIEW );

		// ��������� �������
		glLoadIdentity( );
	}

	inline uint16_t ogl::get_viewport_height( void ) {
		return _viewport_height;
	}

	inline uint16_t ogl::get_viewport_width( void ) {
		return _viewport_width;
	}

	inline uint16_t ogl::get_fov( void ) {
		return _fov;
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
