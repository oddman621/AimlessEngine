#pragma once

#include <GLFW/glfw3.h>
#include <Engine.h>

class glApp
{
private:
	static bool init;
	static int appCount;
protected:
	GLFWwindow* window;
public:
	glApp(const char* title) : glApp(title, 1280, 720, 4, 6) {}
	glApp(const char* title, int width, int height) : glApp(title, width, height, 4, 6) {}
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
	~glApp()
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
