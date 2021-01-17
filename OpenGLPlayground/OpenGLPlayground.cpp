
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <optional>
#include <vector>

#include <Engine.h>

using namespace std;

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
	sp->AddShader("shaders/shader.vert", ShaderProgram::Type::Vertex);
	sp->AddShader("shaders/shader.frag", ShaderProgram::Type::Fragment);
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