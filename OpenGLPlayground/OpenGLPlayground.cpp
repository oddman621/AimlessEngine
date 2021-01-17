
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
	GLFWwindow* window = EngineHelper::GLInit("OpenGLPlayground");

	ShaderProgram* sp = new ShaderProgram();
	sp->AddShader("shaders/shader.vert");
	sp->AddShader("shaders/shader.frag");
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