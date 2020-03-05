#pragma once

/*
 * �� ������ ���� ����� glfw/glew�� �� ���� �ȿ� ����ִ°����� ����� �Ѵ�.
 * �ο쿣�带 �Ű澲�� �ʰ� ������ ���ۿ� ������ �� �ֵ��� �ؾ��Ѵ�.
 * �׷��� ���ӿ����� �����ϴ� �Ŵ�.

 �׷���, �� Ŭ������ ������, �Է°� ���� ��� �� ����Ȱ� �־�� �ϳ�?

 ���� Ŭ������ ��������� �� �����ϴ°� �ʹ� �̸���?
 �׷��ٸ� �ϴ� �� ����Ȱ� �ۼ��Ѵ�.

 Ŭ������ ���Ŀ� ������������� �����Ѵٸ�?
 �׷��ٸ� Ŭ������ ����Ȱ� �ִ� ����� ���� ����� ���� �� �־�� �� ���̴�.

 ������Ʈ ����� �����ұ�?
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