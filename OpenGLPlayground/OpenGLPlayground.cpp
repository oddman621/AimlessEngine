
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <optional>
#include <vector>
#include <list>
#include <map>
#include <utility>

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

class ShaderProgram
{
	GLuint program;
	map<GLuint, string> shaders; // map보다 더 나은 자료구조가 있을까?

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
	string GetShaderLog(GLuint shader)
	{
		string log;
		GLint log_length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
		log.resize(log_length);

		glGetShaderInfoLog(shader, log_length, NULL, log.data());
		if (log_length) log.append("\n");
		return log;
	}
	void ClearShader()
	{
		for (const auto& shader : shaders)
			glDeleteShader(shader.first);
		shaders.clear();
	}
	void RemoveProgram()
	{
		if (program)
			glDeleteProgram(program);
	}
public:
	void AddShader(string file, GLenum type)
	{
		shaders[glCreateShader(type)] = Load(file.c_str());
	}
	void Compile()
	{
		RemoveProgram();
		program = glCreateProgram();

		for (const auto& shader : shaders)
		{
			const char* source = shader.second.data();
			glShaderSource(shader.first, 1, &source, nullptr);
			glCompileShader(shader.first);
			cout << GetShaderLog(shader.first);
			glAttachShader(program, shader.first);
		}
		glLinkProgram(program);
		ClearShader();
	}
};

void error_callback(int error, const char* description)
{
	cerr << "GLFW: (" << error << ") " << description << endl;
	throw runtime_error("GLFW Failed");
}



int main(void)
{
	if (glfwInit() == GLFW_FALSE)
	{
		wcout << L"Failed to init GLFW!" << endl;
		return 0;
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGLPlayground", nullptr, nullptr);
	if (!window) return 0;

	glfwMakeContextCurrent(window);
	if(glewInit() != GLEW_OK) return 0;

	ShaderProgram* sp = new ShaderProgram();
	sp->AddShader("shaders/shader.frag", GL_FRAGMENT_SHADER);
	sp->AddShader("shaders/shader.vert", GL_VERTEX_SHADER);
	sp->Compile();

	while (glfwWindowShouldClose(window) == 0)
	{
		glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete sp;
	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}