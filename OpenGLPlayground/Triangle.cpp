#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Engine.h>

#include "Application.h"

ShaderProgram* sp;
GLuint vao;

STARTUP(Triangle)
{
	sp = new ShaderProgram();
	sp->AddShader("shaders/Triangle.vert");
	sp->AddShader("shaders/Triangle.frag");
	sp->Compile();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

ONLOOP(Triangle)
{
	const GLfloat color[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
	glUseProgram(sp->Get());
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

CLEANUP(Triangle)
{
	glDeleteVertexArrays(1, &vao);
	delete sp;
}