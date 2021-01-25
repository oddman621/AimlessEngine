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
protected:
	virtual void OnLoop(float deltaSecond) = 0;
public:
	virtual void Startup() = 0;
	virtual void Cleanup() = 0;
	void Loop();
};

#define GLAPP(CLASS) \
class CLASS : public glApp \
{\
protected:\
	void OnLoop(float deltaSecond) override;\
public:\
	void Startup() override;\
	void Cleanup() override;\
};