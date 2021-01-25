#include "glApp.h"
#include <GLFW/glfw3.h>
#include <Engine.h>

bool glApp::glfw_initialized = false;
bool glApp::glew_initialized = false;
int glApp::appCount = 0;

glApp::glApp(const char* title, int width, int height, int glMajor, int glMinor)
{
	if (!glfw_initialized)
	{
		glfwInit();
		glfw_initialized = true;
	}

	window = EngineHelper::CreateWindow(title, width, height, glMajor, glMinor);
	appCount += 1;

	// NOTE: ������ glApp ����� ����� ������ ���̴� �ڵ�� ������ ���ɼ��� ���� �κ�
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
	appCount -= 1;
	if (appCount == 0)
	{
		glfwTerminate();
		glfw_initialized = false;
	}
}