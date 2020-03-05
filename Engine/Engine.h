#pragma once

/*
 * 이 엔진을 쓰는 사람은 glfw/glew가 이 엔진 안에 들어있는것조차 몰라야 한다.
 * 로우엔드를 신경쓰지 않고 컨텐츠 제작에 집중할 수 있도록 해야한다.
 * 그래서 게임엔진이 존재하는 거다.

 그래서, 이 클래스가 윈도우, 입력과 같은 모든 걸 끌어안고 있어야 하나?

 지금 클래스가 비대해지는 걸 걱정하는게 너무 이른가?
 그렇다면 일단 다 끌어안고 작성한다.

 클래스가 추후에 비대해졌을때를 가정한다면?
 그렇다면 클래스가 끌어안고 있는 기능을 쉽게 덜어내고 나눌 수 있어야 할 것이다.

 컴포넌트 방식을 적용할까?
*/

class glfwWindowManager
{
public:
    glfwWindowManager();
    virtual ~glfwWindowManager();

private:
    struct GLFWwindow* window;

public:
    int CreateWindow(int width, int height, const char* title);
};

class glewManager
{
public:
    glewManager();
    virtual ~glewManager();
public:
    unsigned int Initialize();
};

class AimlessEngine
{
private:
    const char* title;
public:
    AimlessEngine();
    virtual ~AimlessEngine();
};