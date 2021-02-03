#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ShaderProgram.h>

#include "Apps.h"


static AE::ShaderProgram* sp;
static GLuint vao;

STARTUP(DataBetweenStage)
{
	sp = new AE::ShaderProgram();
	sp->AddShader("shaders/DataBetweenStage.vert");
	sp->AddShader("shaders/DataBetweenStage.frag");
	sp->Compile();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

GLfloat elapsedTime = 0.0f;
ONLOOP(DataBetweenStage)
{
	elapsedTime += deltaSecond;
	const GLfloat clearColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, clearColor);
	glUseProgram(sp->Get());
	glVertexAttrib4f(0, 
		sinf(elapsedTime * 1.5f) * 0.45f, cosf(elapsedTime * 1.5f) * 0.45f, 0.0f, 0.0f);
	glVertexAttrib4f(1, 0.1f, 0.9f, 0.5f, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

CLEANUP(DataBetweenStage)
{
	glDeleteVertexArrays(1, &vao);
	delete sp;
}