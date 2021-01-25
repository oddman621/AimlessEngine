#include "glApp.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Engine.h>

void Triangle::Startup()
{
	sp = new ShaderProgram();
	sp->AddShader("shaders/Triangle.vert");
	sp->AddShader("shaders/Triangle.frag");
	sp->Compile();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void Triangle::Loop()
{
	while (glfwWindowShouldClose(window) == 0)
	{
		const GLfloat color[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);
		glUseProgram(sp->Get());
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Triangle::Cleanup()
{
	glDeleteVertexArrays(1, &vao);
	delete sp;
}