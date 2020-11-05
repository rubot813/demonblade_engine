/*
    Хэдер для подключения OpenGL и библиотек
    Текущие версии:
    GL - 3.2+
    GLU - 3.2
    GLEW - 2.1.0
    GLM - 0.9.9.5
*/

#ifndef INCLUDE_GL_H_INCLUDED
#define INCLUDE_GL_H_INCLUDED

#define GLEW_STATIC	// important, before including glew

#include <GL/glew.h>
// #include <GL/glext.h>	// glext, not gl
// #include <GL/glu.h>	// Not sure
#include <glm.hpp>

#endif // INCLUDE_GL_H_INCLUDED
