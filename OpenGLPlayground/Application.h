#pragma once

#include <glApp.h>

#define GLAPP_CLASS Triangle

class Triangle : public glApp
{
public:
	void Startup();
	void Loop();
	void Cleanup();
};