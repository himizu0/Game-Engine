#pragma once

#include <iostream>
#include <GL/glew.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLCLearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__));

inline void GLCLearError() {
	while (glGetError() != GL_NO_ERROR);
}

inline bool GLLogCall(const char* function, const char* file, int line) {
	GLCall(while (unsigned int error = glGetError()) { )
		printf("[OpenGL Error] ( %i ): %s %s: %i\n", error, function, file, line);
		return false;
	}
	return true;
}