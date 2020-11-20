#include "fp_camera.hpp"

namespace demonblade {
	fp_camera::fp_camera( void ) {
		// Инициализация векторов
		_position	= { .0f, .0f, .0f };
		_center		= { .0f, .0f, .0f };
		_up			= { .0, 1.0f, .0f };
	}

	fp_camera::~fp_camera( void ) {
		// nope. dope. ha
	}

	// ====

	void fp_camera::move_backward( float delta ) {
		_position -= _center * delta;
	}

	void fp_camera::move_forward( float delta ) {
		_position += _center * delta;
	}

	void fp_camera::move_left( float delta ) {
		_position -= glm::normalize( glm::cross( _center, _up ) ) * delta;
	}

	void fp_camera::move_right( float delta ) {
		_position += glm::normalize( glm::cross( _center, _up ) ) * delta;
	}

	void fp_camera::move_down( float delta ) {
		_position -= _up * delta;
	}

	void fp_camera::move_up( float delta ) {
		_position += _up * delta;
	}

	// ====

	void fp_camera::set_angle( glm::vec2 angle ) {
		_angle = angle;
	}

	glm::vec2 fp_camera::get_angle( void ) {
		return _angle;
	}

	// ====

	void fp_camera::add_angle( glm::vec2 val ) {
		_angle += val;
	}

	void fp_camera::calc_center( void ) {
		_center.x = glm::cos( glm::degrees( _angle.y ) ) * glm::cos( glm::degrees( _angle.x ) );
		_center.y = glm::sin( glm::degrees( _angle.y ) );
		_center.z = glm::cos( glm::degrees( _angle.y ) ) * glm::sin( glm::degrees( _angle.x ) );
		_center = glm::normalize( _center );
	}

	void fp_camera::constraint_pitch( float y_up, float y_down ) {
		if ( _angle.y > y_up )
			_angle.y = y_up;

		if ( _angle.y < y_down )
			_angle.y = y_down;
	}

}	// namespace demonblade
