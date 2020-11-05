/*
    Хэдер для подключения OpenGL и библиотек
    Текущие версии:
    GL - 3.2+
    GLEW - 2.1.0
    GLM - 0.9.9.5
*/

#ifndef INCLUDE_GL_H_INCLUDED
#define INCLUDE_GL_H_INCLUDED

#ifndef GLEW_STATIC
	#define GLEW_STATIC	// important, before including glew
#endif	// GLEW_STAIC

#include <GL/glew.h>	//	defines glext, glu
#include <glm.hpp>

#endif // INCLUDE_GL_H_INCLUDED
