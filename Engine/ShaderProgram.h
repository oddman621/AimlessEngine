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
		void ClearShader();
		void RemoveProgram();
		void AddShader(const char* file, GLenum type);
		GLenum GetShaderType(const char* file);
	public:
		void AddShader(const char* file);
		void Compile();


	/// <summary>
	/// functions related to log.
	/// </summary>
	
	// internal function
	private:
		static std::string helper_GetLog(GLuint object,
			void (*GLGetLogLengthFunc)(GLuint, GLuint, GLint*),
			void (*GLGetLogFunc)(GLuint, GLint, GLsizei*, GLchar*));

	// external function
	protected:
		std::string (*GetShaderLog)(GLuint shader) =
			[](GLuint object) -> std::string {
			return helper_GetLog(object, glGetShaderiv, glGetShaderInfoLog);
		};
		std::string (*GetProgramLog)(GLuint program) =
			[](GLuint object) -> std::string {
			return helper_GetLog(object, glGetProgramiv, glGetProgramInfoLog);
		};
	};
}