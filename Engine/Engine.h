#pragma once

// NOTE: 어째서 forward declaration 없이 잘 인식하고 빌드되는 걸까?
//typename GLuint;
//typename GLenum;

#include <string>
#include <vector>

using namespace std;

class ShaderProgram
{
	GLuint program;
	vector<GLuint> shaders;

public:
	ShaderProgram()
	{
		program = 0; shaders.clear();
	}

	virtual ~ShaderProgram()
	{
		RemoveProgram();
		ClearShader();
	}

	GLuint Get()
	{
		return program;
	}

protected:
	string GetShaderLog(GLuint shader);
	string GetProgramLog(GLuint program);
	void ClearShader();
	void RemoveProgram();
	void AddShader(const char* file, GLenum type);
	GLenum GetShaderType(const char* file);
public:
	void AddShader(const char* file);
	void Compile();
};


namespace EngineHelper
{
	string LoadFile(const char* filename);
	void glfwErrorCallback(int error, const char* description);
	GLFWwindow* CreateWindow(const char* title, int width = 1280, int height = 720, int OpenGLmajor = 4, int OpenGLminor = 6);
	GLFWwindow* GLInit(const char* title);
}