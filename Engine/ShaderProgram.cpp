#include <GL/glew.h>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <map>

#include "ShaderProgram.h"
#include "Helper.h"

using namespace std;

namespace AE
{
	string ShaderProgram::helper_GetLog(GLuint object, void(*GLGetLogLengthFunc)(GLuint, GLuint, GLint*), void(*GLGetLogFunc)(GLuint, GLint, GLsizei*, GLchar*))
	{
		string log;
		GLint log_length;
		GLGetLogLengthFunc(object, GL_INFO_LOG_LENGTH, &log_length);
		log.resize(log_length);

		GLGetLogFunc(object, log_length, NULL, log.data());
		if (log_length) log.append("\n");
		return log;
	}

	void ShaderProgram::ClearShader()
	{
		for (GLuint shader : shaders)
			glDeleteShader(shader);
		shaders.clear();
	}
	void ShaderProgram::RemoveProgram()
	{
		if (program)
			glDeleteProgram(program);
	}

	void ShaderProgram::AddShader(const char* file, GLenum type)
	{
		GLuint shader = glCreateShader(type);
		const string&& sourceStr = Helper::LoadFile(file);
		const GLchar* source = sourceStr.data();
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);
		cout << GetShaderLog(shader);
		shaders.push_back(shader);
	}

	GLenum ShaderProgram::GetShaderType(const char* file)
	{
		static map<string, GLenum> extensionMap = {
			make_pair(".vert", GL_VERTEX_SHADER),
			make_pair(".frag", GL_FRAGMENT_SHADER)
		};

		return extensionMap[filesystem::path(file).extension().u8string()];
	}

	void ShaderProgram::AddShader(const char* file)
	{
		AddShader(file, GetShaderType(file));
	}

	void ShaderProgram::Compile()
	{
		RemoveProgram();
		program = glCreateProgram();
		for (GLuint shader : shaders)
			glAttachShader(program, shader);
		glLinkProgram(program);
		cout << GetProgramLog(program);
		ClearShader();
	}
}