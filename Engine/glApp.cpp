#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <chrono>

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

// C++11 표준 Chrono가 간편하고 성능이 상당히 좋다고 하여 사용함
void glApp::Loop()
{
	chrono::system_clock::time_point prevTime = chrono::system_clock::now();
	while (glfwWindowShouldClose(window) == 0)
	{
		chrono::system_clock::time_point currTime = chrono::system_clock::now();
		chrono::duration<float> deltaTime = currTime - prevTime;
		OnLoop(deltaTime.count());

		glfwSwapBuffers(window);
		glfwPollEvents();
		prevTime = currTime;
	}
}