#ifndef GL_LIBS_HPP_INCLUDED
#define GL_LIBS_HPP_INCLUDED

/*
    Хэдер для подключения OpenGL и библиотек
    Текущие версии:
    GL - 3.2+
    GLEW - 2.1.0
    GLM - 0.9.9.5
*/

#ifndef GLEW_STATIC
	#define GLEW_STATIC	// important, before including glew
#endif	// GLEW_STAIC

#include <glew/include/GL/glew.h>	//	defines glext, glu ( for gcc )

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>	// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>	// glm::value_ptr

#endif // GL_LIBS_HPP_INCLUDED
