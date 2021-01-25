#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <optional>
#include <vector>
#include <filesystem>
#include <map>

#include "Helper.h"

using namespace std;

namespace AE::Helper
{
	string LoadFile(const char* filename)
	{
		ifstream file(filename, ios::in);
		optional<string> str;

		if (file.is_open())
		{
			str.emplace();//emplace: optional이 객체를 생성해야함
			file.seekg(0, ios::end);
			streampos length = file.tellg();

			str->resize(length);
			file.seekg(0, ios::beg);
			file.read(str->data(), length);
			file.close();
		}

		return str.value_or("LOAD_FAILURE");
	}

	void glfwErrorCallback(int error, const char* description)
	{
		cerr << "GLFW: (" << error << ") " << description << endl;
		throw runtime_error("GLFW Failed");
	}

	GLFWwindow* CreateWindow(const char* title, int width, int height, int OpenGLmajor, int OpenGLminor)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLmajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLminor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		return window;
	}

	GLFWwindow* GLInit(const char* title, int width, int height, int OpenGLmajor, int OpenGLminor)
	{
		if (glfwInit() == GLFW_FALSE)
		{
			cerr << "EngineHelper::GLInit : Failed to init GLFW!" << endl;
			return nullptr;
		}

		glfwSetErrorCallback(glfwErrorCallback);

		GLFWwindow* window = CreateWindow(title, width, height, OpenGLmajor, OpenGLminor);

		if (!window)
			cerr << "EngineHelper::GLinit : Failed to Create GLFWwindow!" << endl;
		else
		{
			glfwMakeContextCurrent(window);
			if (glewInit() != GLEW_OK)
			{
				cerr << "EngineHelper::GLInit : Failed to init GLEW!" << endl;
				glfwDestroyWindow(window);
				window = nullptr;
			}
			glfwSwapInterval(1);
		}

		return window;
	}
}

