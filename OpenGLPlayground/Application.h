#pragma once

#include <glApp.h>

#define GLAPP_CLASS Triangle

class Triangle : public glApp
{
protected:
	void OnLoop(float deltaSecond) override;
public:
	void Startup() override;
	void Cleanup() override;
};