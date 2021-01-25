
#include "pch.h"
#include "Engine.h"
#include "glApp.h"

GLFWwindow* glApp::window = nullptr;

glApp::glApp(const char* title, int width, int height, int glMajor, int glMinor)
{
	if (window) 
		throw runtime_error("glApp : Window already created");

	window = EngineHelper::GLInit(title, width, height, glMajor, glMinor);
}

glApp::~glApp()
{
	glfwDestroyWindow(window);
	window = nullptr;
	glfwTerminate();
}