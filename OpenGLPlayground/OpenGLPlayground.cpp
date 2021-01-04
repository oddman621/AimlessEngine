
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <optional>
#include <vector>

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
	string GetProgramLog(GLuint program)
	{
		string log;
		GLint log_length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
		log.resize(log_length);

		glGetProgramInfoLog(program, log_length, NULL, log.data());
		if (log_length) log.append("\n");
		return log;
	}
	void ClearShader()
	{
		for (GLuint shader : shaders)
			glDeleteShader(shader);
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
		GLuint shader = glCreateShader(type);
		string source = Load(file.c_str());
		const GLchar* const source_ptr = source.c_str();
		glShaderSource(shader, 1, &source_ptr, nullptr);
		glCompileShader(shader);
		cout << GetShaderLog(shader);

		shaders.push_back(shader);
	}
	void Compile()
	{
		RemoveProgram();
		program = glCreateProgram();
		for (GLuint shader : shaders)
			glAttachShader(program, shader);
		glLinkProgram(program);
		cout << GetProgramLog(program);
		ClearShader();
	}
};

void glfwErrorCallback(int error, const char* description)
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

	glfwSetErrorCallback(glfwErrorCallback);

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

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	while (glfwWindowShouldClose(window) == 0)
	{
		const GLfloat color[4] = {0.1f, 0.1f, 0.1f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, color);
		glUseProgram(sp->Get());
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	delete sp;
	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}