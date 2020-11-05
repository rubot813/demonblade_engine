#ifndef CORE_HPP_INCLUDED
#define CORE_HPP_INCLUDED

#include <cstdint>

// todo: light

namespace demonblade {

class core {
public:
	static core* get_instance( void ) {
		static core core_instance;	// lazy :<
		return &core_instance;
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
	// ��������� ������� ����� ������ ( ���� ) ��� �����������
	bool init( uint16_t window_width, uint16_t window_height );

	// ������� ��������� �������� ����
	void reshape( uint16_t window_width, uint16_t window_height );

	// ������� ������� ������� MODELVIEW � ������� OpenGL
	void clear( void );

	// ������� ��������� / ���������� ������������ OpenGL
	void enable( func_e type );
	void disable( func_e type );
	void select( func_e type, bool state );

private:
	// ������ ������������, �����������, �������� �����������
	core( void ) { };
	~core( void ) { };
	core( const core &_ex ) = delete;
	core& operator=( const core& ) = delete;

protected:
	// no childs allowed
};	// core

namespace fog {
// ��������� ���������� ������
// ������, �����, ���������
void set( float start, float end, float density );

}	// namespace fog

namespace light {
	// todo
}	// namespace light

} // namespace demonblade

#endif // CORE_HPP_INCLUDED
