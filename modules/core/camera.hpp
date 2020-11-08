#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include "../common/gl_libs.hpp"

/*
	����� ��������� ������ ������
*/

namespace demonblade {

	class camera {
		public:
			// ����������� �� ���������
			camera( void );

			// ������������� �����������, ������ �������� set_viewport
			camera( uint16_t width, uint16_t height, float fov, float z_near = 1.0f, float z_far = 250.0f );

			~camera( void );

			// ������ ��������� ���������� ������
			inline void set_position( glm::vec3 value );
			inline void set_center( glm::vec3 value );
			inline void set_up( glm::vec3 value );

			// ������ ��������� ���������� ������
			inline glm::vec3 get_position( void );
			inline glm::vec3 get_center( void );
			inline glm::vec3 get_up( void );

			// ����� ��������� ����� ������
			// ��� ����������� ��������� ������� � private
			void set_viewport( uint16_t width, uint16_t height, float fov, float z_near = 1.0f, float z_far = 250.0f );

			// ����� ������������� �� ���� ������� ������
			void project( void );

			// ������
		private:
			// ����� ������������� ������� �������� GL_PROJECTION �� ���������� ����� ������
			void _set_projection_matrix( void );


			// ����������
		private:

			// ������� ������ ( ����� ���������� )
			glm::vec3	_position;

			// ���� ������� ������ ( ����� ���������� )
			glm::vec3	_center;

			// ����������� ������ �����
			glm::vec3	_up;

			// ������� ����� ������
			uint16_t	_viewport_width;
			uint16_t	_viewport_height;

			// ���� ������ � ��������
			float	_fov;

			// ������� � ������� ��������� �������� ���������
			float		_z_near;
			float		_z_far;

	};	// camera class

}	// namespace demonblade

#endif // CAMERA_HPP_INCLUDED
