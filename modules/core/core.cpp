#include "core.hpp"
#include "../common/include_gl.hpp"

namespace demonblade {

bool core::init( uint16_t window_width, uint16_t window_height ) {

	// ������������� GLEW � ��������� ������
	GLenum glew_init_error = glewInit( );
	if ( glew_init_error != GLEW_OK )
		return 0;

	// ������������� OpenGL

	// ��������� ����� ������� ����� ������ � RGBA
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	// ��������� ������� �������
	glClearDepth( 1.0d );

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

	// ��������� �������� ����� ������
	reshape( window_width, window_height );

	return 1;
}

void core::enable( func_e type ) {
	glEnable( type );
}

void core::disable( func_e type ) {
	glDisable( type );
}

void core::select( func_e type, bool state ) {
	state ? glEnable( type ) : glDisable( type );
}

void core::clear( void ) {
	// ������� ������ ������� � �����
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// ������� ������ �������
	glClear( GL_DEPTH_BUFFER_BIT );
}

void core::reshape( uint16_t window_width, uint16_t window_height ) {
	// ��������� ��������� � ������� ����� ������
	glViewport( 0, 0, window_width, window_height );

	// ����� ������� ��������
	glMatrixMode( GL_PROJECTION );

	// ��������� ������� ��������
	glLoadIdentity( );

	// ����������� ������� ���������� ������������� ��������:
	// ���� ������ �� ��� Y
	// ����������� ������ ������
	// ������� ��������� ��������� �������� ����������
	// ������� ��������� ��������� �������� ����������
	gluPerspective( 70.0f, ( ( float ) window_width / ( float )window_height ), 1.0f, 250.0f );

	// ����� ������� ���������� �������
	glMatrixMode( GL_MODELVIEW );

	// ��������� �������
	glLoadIdentity( );
}

void fog::set( float start, float end, float density ) {
	// Enable fog
	// core::get_instance( ).enable( core::FOG );

	//������
	glFogf( GL_FOG_START, ( GLfloat )start);

	//�����
	glFogf( GL_FOG_END, ( GLfloat )end );

	//���������
	glFogf( GL_FOG_DENSITY,( GLfloat ) density );
}

} //namespace demonblade
