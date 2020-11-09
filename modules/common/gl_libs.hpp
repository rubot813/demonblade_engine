#ifndef GL_LIBS_HPP_INCLUDED
#define GL_LIBS_HPP_INCLUDED

/*
    Хэдер для подключения OpenGL и библиотек
    Текущие версии:
    GL - 3.2+
    GLEW - 2.1.0
    GLM - 0.9.9.5

    Подключение:
    compiler: путь до папки external
    linker:	путь external/glew/lib/gcc или external/glew/lib/vc
    linker flags: glew32 opengl32
*/

#ifndef GLEW_STATIC
	#define GLEW_STATIC	// important, before including glew
#endif	// GLEW_STAIC

#include <glew/include/GL/glew.h>	//	defines glext, glew

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>	// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>	// glm::value_ptr

#endif // GL_LIBS_HPP_INCLUDED
