#pragma once

// pch�� ���ԵǾ� �ش� forward declaration�� �ʿ������ ������ ����... ��Ȯ�� ������ ��
//typedef GLuint;
//typedef GLenum;
//class string;

using namespace std;

class ShaderProgram
{
	GLuint program;
	vector<GLuint> shaders;

public:
	enum class Type
	{
		Auto, 
		Vertex, Fragment
	};

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
	void AddShader(GLenum type, const char* file);
public:
	void AddShader(const char* file, Type type = Type::Auto);
	void Compile();
};


namespace EngineHelper
{
	void glfwErrorCallback(int error, const char* description);
	GLFWwindow* CreateWindow(const char* title, int width = 1280, int height = 720, int OpenGLmajor = 4, int OpenGLminor = 6);
}