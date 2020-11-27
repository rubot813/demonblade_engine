#ifndef DRAWABLE_HPP_INCLUDED
#define DRAWABLE_HPP_INCLUDED

#include "../common/global.hpp"
#include "../common/db_glm.hpp"

namespace demonblade {
	class drawable {

		public:

			// ������ �����������, �������� � ���������������
			void move( glm::vec3 offset );
			void rotate( glm::vec3 offset );
			void scale( glm::vec3 offset );

			// ������ ��������� �������, �������� � ��������
			void set_position( glm::vec3 value );
			void set_rotation( glm::vec3 value );
			void set_scale( glm::vec3 value );

			// ������ ��������� �������, �������� � ��������
			glm::vec3 get_position( void );
			glm::vec3 get_rotation( void );
			glm::vec3 get_scale( void );

			// ������ ��������� �������� ����������
			void set_ambient( glm::vec4 value );
			void set_diffuse( glm::vec4 value );
			void set_specular( glm::vec4 value );

			// ������ ��������� �������� ����������
			glm::vec4 get_ambient( void );
			glm::vec4 get_diffuse( void );
			glm::vec4 get_specular( void );

			// ����� ���������
			virtual void render( void );

		protected:

			// ������� ���������: ���������, �������� � ���������������
			glm::vec3 _position;
			glm::vec3 _rotation;
			glm::vec3 _scale;

			// �������� ���������
			glm::vec4 _ambient;		// ���������� ����
			glm::vec4 _diffuse;		// ��������� ����
			glm::vec4 _specular;	// ���������� ����

	};	// class drawable

}	// namespace demonblade

#endif // DRAWABLE_HPP_INCLUDED
