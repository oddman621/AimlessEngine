#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <iostream>

#include "Helper.h"
#include "glApp.h"

GLFWwindow* glApp::window = nullptr;

glApp::glApp(const char* title, int width, int height, int glMajor, int glMinor)
{
	if (window) 
		throw std::runtime_error("glApp : Window already created");

	window = AE::Helper::GLInit(title, width, height, glMajor, glMinor);
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
	std::chrono::system_clock::time_point prevTime = std::chrono::system_clock::now();
	while (glfwWindowShouldClose(window) == 0)
	{
		std::chrono::system_clock::time_point currTime = std::chrono::system_clock::now();
		std::chrono::duration<float> deltaTime = currTime - prevTime;
		OnLoop(deltaTime.count());

		glfwSwapBuffers(window);
		glfwPollEvents();
		prevTime = currTime;
	}
}