#pragma once

// pch�� ���ԵǾ� �ش� forward declaration�� �ʿ������ ������ ����... ��Ȯ�� ������ ��
//typedef GLuint;
//typedef GLenum;
//class string;

using namespace std;

string Load(const char* filename);
class ShaderProgram
{
	GLuint program;
	vector<GLuint> shaders;

public:
	enum Type
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
	void AddShader(const char* file, Type type = Auto);
	void Compile();
};

void glfwErrorCallback(int error, const char* description);