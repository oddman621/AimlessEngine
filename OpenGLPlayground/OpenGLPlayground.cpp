
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <optional>
#include <vector>
#include <list>

using namespace std;

string Load(const char* filename)
{
	ifstream file(filename, ios::in);
	optional<string> str;

	if (file.is_open())
	{
		//optional이 실질적으로 객체를 생성해야만 제대로 작동함. emplace는 그 일환으로 호출됨.
		//Workaround 해결법이므로 실질적 해결방법 찾을 필요 있음
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
	//1쉐이더 1파일인데, 이걸 변경할 필요가 있나?
	void AddShader(string file, GLenum type)
	{
		GLuint shader = glCreateShader(type);
		const GLchar* source = Load(file.c_str()).c_str();
		glShaderSource(shader, 1, &source, nullptr);
		shaders.push_back(shader);
	}
	void Compile()
	{
		RemoveProgram();
		program = glCreateProgram();

		for (GLuint shader : shaders)
		{
			glCompileShader(shader);
			cout << GetShaderLog(shader) << endl;
			glAttachShader(program, shader);
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