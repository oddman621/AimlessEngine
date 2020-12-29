
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <optional>
#include <vector>
#include <list>

using namespace std;

optional<wstring> Load(const wchar_t* filename)
{
	wifstream file(filename, ios::in);
	optional<wstring> str;

	if (file.is_open())
	{
		str.emplace();
		file.seekg(0, ios::end);
		wstreampos length = file.tellg();

		str->resize(length);
		file.seekg(0, ios::beg);
		file.read(str->data(), length);
		file.close();
	}
	
	return str;
}

struct ShaderInfo
{
	wstring sourceFile;
	GLenum shaderType;
	ShaderInfo() : sourceFile(L""), shaderType(0) {}
	ShaderInfo(wstring file, GLenum type) : sourceFile(file), shaderType(type) {}
};

class Shader
{
	GLint64 shader;
	ShaderInfo shaderInfo;
	Shader(ShaderInfo info)
	{
		shaderInfo = info;
		CompileShader();
	}
	void CompileShader()
	{
		CompileShader(shaderInfo);
	}
	void CompileShader(ShaderInfo info)
	{

	}

	const GLint64 Get()
	{
		return shader;
	}
};

class ShaderProgram
{
	GLint64 program;
	std::list<ShaderInfo> shaderInfos;
	std::vector<GLint64> shaders;
	std::vector<wstring> shaderSources;

public:
	bool AddShader(wstring file, GLenum type)
	{
		return AddShader(ShaderInfo(file, type));
	}
	bool AddShader(ShaderInfo info)
	{

	}
	bool AddShader(ShaderInfo* infos)
	{

	}
	void RemoveProgram(bool clearShader = true)
	{

	}
	bool Build()
	{

	}
};

void error_callback(int error, const char* description)
{

}



int main(void)
{
	if (glfwInit() == GLFW_FALSE)
	{
		wcout << L"Failed to init GLFW!" << endl;
		return 0;
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGLPlayground", nullptr, nullptr);
	if (!window) return 0;

	glfwMakeContextCurrent(window);
	if(glewInit() != GLEW_OK) return 0;

	while (glfwWindowShouldClose(window) == 0)
	{
		glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}