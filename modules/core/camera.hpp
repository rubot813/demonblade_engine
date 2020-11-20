#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include "../common/db_glm.hpp"
#include "../common/global.hpp"

/*
	����� ��� ������� ������ � �������. ������ ������� - ��������� ���
	������, ����� ������� ����� �����
*/

namespace demonblade {

	class camera {
		public:

			camera( void );

			~camera( void );

			// ����� ��������� ����� ������
			// ��� ����������� ��������� ������� � private
			void set_viewport( uint16_t width, uint16_t height, float fov = 60.0f, float z_near = 0.1f, float z_far = 250.0f );

			// ����� �������������
			// ������������� ������� modelview
			void view( void );

			// ====

			// ������ ��������� ���������� ������
			void set_position( glm::vec3 value );
			void set_center( glm::vec3 value );
			void set_up( glm::vec3 value );

			// ������ ��������� ���������� ������
			glm::vec3 get_position( void );
			glm::vec3 get_center( void );
			glm::vec3 get_up( void );

			// ====

			// ����������
		protected:

			// ������� ������ ( ����� ���������� )
			glm::vec3	_position;

			// ����������� ������
			glm::vec3	_center;

			// ������������ ������. ������ ���� { 0.0f, 1.0f, 0.0f }
			glm::vec3	_up;

	};	// camera class

}	// namespace demonblade

#endif // CAMERA_HPP_INCLUDED
