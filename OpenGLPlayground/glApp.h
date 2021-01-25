#pragma once

#include <GLFW/glfw3.h>
#include <Engine.h>

class glApp
{
private:
	static bool init;
	static int appCount;
	const char* const DEFAULT_TITLE = "glApp";
	const int DEFAULT_WIDTH = 1280;
	const int DEFAULT_HEIGHT = 720;
	const int DEFAULT_GLMAJOR = 4;
	const int DEFAULT_GLMINOR = 6;
protected:
	GLFWwindow* window;
public:
	glApp() : glApp(DEFAULT_TITLE, DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_GLMAJOR, DEFAULT_GLMINOR) {}
	glApp(const char* title) : glApp(title, DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_GLMAJOR, DEFAULT_GLMINOR) {}
	glApp(const char* title, int width, int height) : glApp(title, width, height, DEFAULT_GLMAJOR, DEFAULT_GLMINOR) {}
	glApp(const char* title, int width, int height, int glMajor, int glMinor)
	{
		if (!init)
		{
			glfwInit();
			init = true;
		}
		window = EngineHelper::CreateWindow(title, width, height, glMajor, glMinor);
		appCount += 1;
	}
	virtual ~glApp()
	{
		glfwDestroyWindow(window);
		appCount -= 1;
		if (appCount == 0) 
		{ 
			glfwTerminate(); 
			init = false;
		}
	}
public:
	virtual void Startup() = 0;
	virtual void Loop() = 0;
	virtual void Cleanup() = 0;
};
bool glApp::init = false;
int glApp::appCount = 0;

class Triangle : public glApp
{
	void Startup();
	void Loop();
	void Cleanup();
};
