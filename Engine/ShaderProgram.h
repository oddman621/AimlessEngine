#pragma once

typedef GLuint;
typedef GLenum;

#include <string>
#include <vector>


namespace AE
{
	class ShaderProgram
	{
		GLuint program;
		std::vector<GLuint> shaders;

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
		std::string GetShaderLog(GLuint shader);
		std::string GetProgramLog(GLuint program);
		void ClearShader();
		void RemoveProgram();
		void AddShader(const char* file, GLenum type);
		GLenum GetShaderType(const char* file);
	public:
		void AddShader(const char* file);
		void Compile();
	};
}