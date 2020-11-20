#ifndef DB_GL_HPP_INCLUDED
#define DB_GL_HPP_INCLUDED

/*
    ����� ��� ����������� OpenGL � ���������� GLEW
    ������� ������:
    GL - 3.2+
    GLEW - 2.1.0

    �����������:
    compiler: ���� �� ����� external
    linker:	���� external/glew/lib/gcc ��� external/glew/lib/vc
    linker flags: glew32 opengl32
*/

#ifndef GLEW_STATIC
	#define GLEW_STATIC	// important, before including glew
#endif	// GLEW_STAIC
#include <glew/include/GL/glew.h>	//	defines glext, glew

#endif // DB_GL_HPP_INCLUDED
