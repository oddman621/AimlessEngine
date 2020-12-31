
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

optional<string> Load(const char* filename)
{
	ifstream file(filename, ios::in);
	optional<string> str;

	if (file.is_open())
	{
		str.emplace();
		file.seekg(0, ios::end);
		streampos length = file.tellg();

		str->resize(length);
		file.seekg(0, ios::beg);
		file.read(str->data(), length);
		file.close();
	}

	return str;
}



class ShaderProgram
{
	GLuint program;
	std::vector<GLuint> shaders;

public:
	ShaderProgram()
	{
		program = 0; shaders.clear();
	}

	GLuint Get()
	{
		return program;
	}

protected:

public:
	bool AddShader(string file, GLenum type)
	{
		GLuint shader = glCreateShader(type);
		const GLchar* source = Load(file.c_str())->c_str();
		glShaderSource(shader, 1, &source, nullptr);
	}
	void ClearShader()
	{

	}
	void RemoveProgram(bool clearShader = true)
	{

		if (clearShader) ClearShader();
	}
	bool Build()
	{

	}
};

void error_callback(int error, const char* description)
{
	std::cerr << "GLFW: (" << error << ") " << description << std::endl;
	throw std::runtime_error("GLFW Failed");
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

	while (glfwWindowShouldClose(window) == 0)
	{
		glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}