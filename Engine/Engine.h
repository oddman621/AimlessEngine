#pragma once

// pch에 포함되어 해당 forward declaration이 필요없어진 것으로 보임... 정확한 이유는 모름
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