// Engine.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"

using namespace std;

string EngineHelper::LoadFile(const char* filename)
{
	ifstream file(filename, ios::in);
	optional<string> str;

	if (file.is_open())
	{
		str.emplace();//emplace: optional이 객체를 생성해야함
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

void ShaderProgram::AddShader(const char* file, GLenum type)
{
	GLuint shader = glCreateShader(type);
	const string&& sourceStr = EngineHelper::LoadFile(file);
	const GLchar* source = sourceStr.data();
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);
	cout << GetShaderLog(shader);
	shaders.push_back(shader);
}

void ShaderProgram::AddShader(const char* file)
{
	static map<string, GLenum> extensionMap = {
		make_pair(".vert", GL_VERTEX_SHADER),
		make_pair(".frag", GL_FRAGMENT_SHADER)
	};

	const string&& extension = filesystem::path(file).extension().u8string();

	AddShader(file, extensionMap[extension]);
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

void EngineHelper::glfwErrorCallback(int error, const char* description)
{
	cerr << "GLFW: (" << error << ") " << description << endl;
	throw runtime_error("GLFW Failed");
}

GLFWwindow* EngineHelper::CreateWindow(const char* title, int width, int height, int OpenGLmajor, int OpenGLminor)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLmajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLminor);
	GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	
	if (!window)
		wcerr << L"Engine::CreateWindow : Failed to create glfwWindow!" << endl;

	return window;
}

GLFWwindow* EngineHelper::GLInit(const char* title)
{
	if (glfwInit() == GLFW_FALSE)
	{
		wcout << L"EngineHelper::GLInit : Failed to init GLFW!" << endl;
		return nullptr;
	}

	glfwSetErrorCallback(EngineHelper::glfwErrorCallback);

	GLFWwindow* window = EngineHelper::CreateWindow("OpenGLPlayground");
	
	if (!window)
	{
		wcout << L"EngineHelper::GLinit : Failed to Create GLFWwindow!" << endl;
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
	{
		wcout << L"EngineHelper::GLInit : Failed to init GLEW!" << endl;
		glfwDestroyWindow(window);
		return nullptr;
	}

	return window;
}

