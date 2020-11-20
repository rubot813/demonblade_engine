#ifndef FP_CAMERA_HPP_INCLUDED
#define FP_CAMERA_HPP_INCLUDED

#include "camera.hpp"
#include "../common/gl_libs.hpp"

/*
	����� ��������� ������ ������ �� ������� ���� ( first - person camera )
	������� �� ������� ������ camera
*/

namespace demonblade {

	class fp_camera : public camera {
		public:

			fp_camera( void );

			~fp_camera( void );

			// ������ ������������ ������ ������������ ����������� �������
			// ��������� ������ ( �������� ) �� ������� �������������
			void move_backward( float delta );
			void move_forward( float delta );
			void move_left( float delta );
			void move_right( float delta );
			void move_down( float delta );
			void move_up( float delta );

			// ����� ��������� ���� �������� ������
			// ��������� ���� � ��������
			void set_angle( glm::vec2 angle );

			// ����� ��������� ���� �������� ������
			// ���������� �������� � ��������
			glm::vec2 get_angle( void );

			// ����� ���������� ���� � ���� �������� ������
			void add_angle( glm::vec2 val );

			// ����� ������������ ������������ ���� �������� ������
			void constraint_pitch( float y_up = 0.027f, float y_down = -0.027f );

			// ����� ������� ������� ����������� ������ �� �������� ����� ������
			void calc_center( void );

		private:

			// ������, ����������� ���� �������� ������ ( ���� ������ )
			// x : yaw ( �������������� ��� )
			// y : pitch ( ������������ ��� )
			glm::vec2 _angle;

	};	// fp_camera class

}	// namespace demonblade

#endif // CAMERA_HPP_INCLUDED
