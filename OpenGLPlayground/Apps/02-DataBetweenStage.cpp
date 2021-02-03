#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ShaderProgram.h>

#include "Apps.h"


AE::ShaderProgram* sp;
GLuint vao;

STARTUP(DataBetweenStage)
{
	sp = new AE::ShaderProgram();
	sp->AddShader("shaders/DataBetweenStage.vert");
	sp->AddShader("shaders/DataBetweenStage.frag");
	sp->Compile();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

ONLOOP(DataBetweenStage)
{
	const GLfloat color[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
	glUseProgram(sp->Get());
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

CLEANUP(DataBetweenStage)
{
	glDeleteVertexArrays(1, &vao);
	delete sp;
}