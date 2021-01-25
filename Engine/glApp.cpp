
#include "pch.h"
#include "Engine.h"
#include "glApp.h"

bool glApp::glfw_initialized = false;
bool glApp::glew_initialized = false;
GLFWwindow* glApp::window = nullptr;

glApp::glApp(const char* title, int width, int height, int glMajor, int glMinor)
{
	if (!glfw_initialized)
	{
		glfwInit();
		glfw_initialized = true;
	}
	glfwSetErrorCallback(EngineHelper::glfwErrorCallback);

	window = EngineHelper::CreateWindow(title, width, height, glMajor, glMinor);

	glfwMakeContextCurrent(window);
	if (!glew_initialized)
	{
		glewInit();
		glew_initialized = true;
	}
	glfwSwapInterval(1);
}

glApp::~glApp()
{
	glfwDestroyWindow(window);
	window = nullptr;
	glfwTerminate();
	glfw_initialized = false;
}