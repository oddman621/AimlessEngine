// Engine.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"

using namespace std;

string Load(const char* filename)
{
	ifstream file(filename, ios::in);
	optional<string> str; //optional 쓰고싶었음

	if (file.is_open())
	{
		//emplace: optional이 객체를 생성해야함
		str.emplace();
		file.seekg(0, ios::end);
		streampos length = file.tellg();

		str->resize(length);
		file.seekg(0, ios::beg);
		file.read(str->data(), length);
		file.close();
	}

	return str.value_or("LOAD_FAILURE");
}

string ShaderProgram::GetShaderLog(GLuint shader)
{
	string log;
	GLint log_length;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
	log.resize(log_length);

	glGetShaderInfoLog(shader, log_length, NULL, log.data());
	if (log_length) log.append("\n");
	return log;
}
string ShaderProgram::GetProgramLog(GLuint program)
{
	string log;
	GLint log_length;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
	log.resize(log_length);

	glGetProgramInfoLog(program, log_length, NULL, log.data());
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

void ShaderProgram::AddShader(GLenum type, const char* file)
{
	GLuint shader = glCreateShader(type);
	const string&& sourceStr = Load(file);
	const GLchar* source = sourceStr.data();
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);
	cout << GetShaderLog(shader);
	shaders.push_back(shader);
}
void ShaderProgram::AddShader(const char* file, Type type)
{
	switch (type)
	{
	case Vertex:
		AddShader(GL_VERTEX_SHADER, file);
		break;
	case Fragment:
		AddShader(GL_FRAGMENT_SHADER, file);
		break;
	case Auto: // TODO: 셰이더 타입 자동추론기능
		wcerr << L"AddShader: 현재 셰이더 자동추론기능이 없습니다." << endl;
		break;
	default:
		wcerr << L"AddShader: 알 수 없는 셰이더 타입입니다." << endl;
		break;
	}
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

void glfwErrorCallback(int error, const char* description)
{
	cerr << "GLFW: (" << error << ") " << description << endl;
	throw runtime_error("GLFW Failed");
}

