#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ShaderProgram.h>

#include "Apps.h"


AE::ShaderProgram* sp;
GLuint vao;

STARTUP(Triangle)
{
	sp = new AE::ShaderProgram();
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