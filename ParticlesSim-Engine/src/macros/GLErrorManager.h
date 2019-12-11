#pragma once

#include <GL/glew.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak()

#define GLCALL(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__));

static void GLClearError() {
	while (glGetError());
}

static bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cerr << "[OpenGL Error Code]: " << error << std::endl
			<< "\tFunction: " << function << std::endl
			<< "\tFile: " << file << std::endl
			<< "\tLine: " << line << std::endl;
		return false;
	}
	return true;
}