
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

void glApp::Loop()
{
	auto prevTime = chrono::system_clock::now();
	while (glfwWindowShouldClose(window) == 0)
	{
		auto currTime = chrono::system_clock::now();
		chrono::duration<float> deltaTime = currTime - prevTime;
		OnLoop(deltaTime.count());

		glfwSwapBuffers(window);
		glfwPollEvents();
		prevTime = currTime;
	}
}