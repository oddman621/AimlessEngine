#pragma once
#include <string>

struct GLFWwindow;

namespace AE::Helper
{
	std::string LoadFile(const char* filename);
	void glfwErrorCallback(int error, const char* description);
	GLFWwindow* CreateWindow(const char* title, int width = 1280, int height = 720, int OpenGLmajor = 4, int OpenGLminor = 6);
	GLFWwindow* GLInit(const char* title, int width = 1280, int height = 720, int OpenGLmajor = 4, int OpenGLminor = 6);
}