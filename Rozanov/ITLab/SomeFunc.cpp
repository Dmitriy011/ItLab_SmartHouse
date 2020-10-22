// GLEW ����� ���������� �� GLFW.
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include <iostream>

#include "SomeFunc.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)	//�������: 1�������� ��������� �� GLFWwindow, 2�� ����� ����������� ������� �������, 3�� �������� �������������� ��� ��������, 4�� ����� ����������� ������������ (shift, control, alt ��� super). ����� ����� ������ �������, GLFW ������� ��� ������� � �������� � ��� ��������� ���������.
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)								// ����� ������������ ��������(�� ������)(GLFW_PRESS) ESC, ������������� �������� WindowShouldClose � true - � ���������� ����� ����� ���������
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}