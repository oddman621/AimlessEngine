#pragma once

struct GLFWwindow;

class glApp
{
	static inline const char* const DEFAULT_TITLE = "glApp";
	static inline const int DEFAULT_WIDTH = 1280;
	static inline const int DEFAULT_HEIGHT = 720;
	static inline const int DEFAULT_GLMAJOR = 4;
	static inline const int DEFAULT_GLMINOR = 6;
private:
	static GLFWwindow* window;
public:
	glApp() : glApp(DEFAULT_TITLE, DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_GLMAJOR, DEFAULT_GLMINOR) {}
	glApp(const char* title) : glApp(title, DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_GLMAJOR, DEFAULT_GLMINOR) {}
	glApp(const char* title, int width, int height) : glApp(title, width, height, DEFAULT_GLMAJOR, DEFAULT_GLMINOR) {}
	glApp(const char* title, int width, int height, int glMajor, int glMinor);
	virtual ~glApp();
public:
	GLFWwindow* GetWindow() { return window; }
public:
	virtual void Startup() = 0;
	virtual void Loop() = 0;
	virtual void Cleanup() = 0;
};