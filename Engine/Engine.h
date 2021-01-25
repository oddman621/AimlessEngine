#pragma once

// NOTE: ��°�� forward declaration ���� �� �ν��ϰ� ����Ǵ� �ɱ�?
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