#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glApp.h>

#define GLAPP_CLASS Triangle

class Triangle : public glApp
{
	class ShaderProgram* sp;
	GLuint vao;
public:
	void Startup();
	void Loop();
	void Cleanup();
};