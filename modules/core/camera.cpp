#include "camera.hpp"

namespace demonblade {
	camera::camera( void ) {
		_up = { .0, 1.0f, .0f };
	}

	camera::camera( uint16_t width, uint16_t height, float fov, float z_near, float z_far ) {
		_up = { .0, 1.0f, .0f };
		set_viewport( width, height, fov, z_near, z_far );
	}

	camera::~camera( void ) {

	}

	void camera::set_viewport( uint16_t width, uint16_t height, float fov, float z_near, float z_far ) {
		// ���������� ����������
		_viewport_width		= width;
		_viewport_height	= height;
		_fov				= fov;
		_z_near				= z_near;
		_z_far				= z_far;

		// ��������� ������� ��������
		_set_projection_matrix( );

	}

	void camera::_set_projection_matrix( void ) {
		// ��������� ��������� � ������� ����� ������
		glViewport( 0, 0, _viewport_width, _viewport_height );

		// ����� ������� ��������
		glMatrixMode( GL_PROJECTION );

		// ��������� ������� ��������
		glLoadIdentity( );

		// ������ ����������� ������ ������
		float aspect_ratio = ( ( float )_viewport_width / ( float )_viewport_height );

		float _fov_checked;
		#ifdef GLM_FORCE_RADIANS
		_fov_checked = glm::radians( _fov );	// deg_to_rad
		#else
		_fov_checked = _fov;
		#endif // GLM_FORCE_RADIANS

		// ����������� ������� ���������� ������������� �������� ( GL_PROJECTION ):
		// ���� ������ �� ��� Y
		// ����������� ������ ������
		// ������� ��������� ��������� �������� ����������
		// ������� ��������� ��������� �������� ����������
		//glm::mat4 projection_mat = glm::perspective( _fov_checked, aspect_ratio, _z_near, _z_far );	// todo: magic nums?
		//glLoadMatrixf( glm::value_ptr( projection_mat ) );
		gluPerspective( _fov_checked, aspect_ratio, 0.1f, 250.0f );

		// ����� ������� ���������� �������
		glMatrixMode( GL_MODELVIEW );

		// ��������� �������
		glLoadIdentity( );
	}

	void camera::project( void ) {

		// ��������� ������� MODELVIEW
		glLoadIdentity( );

		//glm::mat4 lookat_mat = glm::lookAt( _position, _center, _up );
		//glLoadMatrixf( glm::value_ptr( lookat_mat ) );
		gluLookAt( _position.x, _position.y, _position.z,
					_center.x, _center.y, _center.z,
					_up.x, _up.y, _up.z );

	}

	void camera::set_position( glm::vec3 value ) {
		_position = value;
	}

	void camera::set_center( glm::vec3 value ) {
		_center = value;
	}

	void camera::set_up( glm::vec3 value ) {
		_up = value;
	}

	glm::vec3 camera::get_position( void  ) {
		return _position;
	}

	glm::vec3 camera::get_center( void  ) {
		return _center;
	}

	glm::vec3 camera::get_up( void ) {
		return _up;
	}
}	// namespace demonblade
