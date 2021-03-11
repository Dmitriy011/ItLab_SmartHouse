// GLEW ����� ���������� �� GLFW.
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include <iostream>

#include "Utils.h"

void Utils::movement()
{
    if (intilizaton.keys[GLFW_KEY_W])
    {
        camera.ProcessKeyboard(FORWARD, intilizaton.deltaTime);
    }
    if (intilizaton.keys[GLFW_KEY_S])
    {
        camera.ProcessKeyboard(BACKWARD, intilizaton.deltaTime);
    }
    if (intilizaton.keys[GLFW_KEY_A])
    {
        camera.ProcessKeyboard(LEFT, intilizaton.deltaTime);
    }
    if (intilizaton.keys[GLFW_KEY_D])
    {
        camera.ProcessKeyboard(RIGHT, intilizaton.deltaTime);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (intilizaton.firstMouse)
    {
        intilizaton.lastX = xpos;
        intilizaton.lastY = ypos;
        intilizaton.firstMouse = false;
    }

    GLfloat xoffset = xpos - intilizaton.lastX;
    GLfloat yoffset = intilizaton.lastY - ypos;

    intilizaton.lastX = xpos;
    intilizaton.lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)//�������: 1�������� ��������� �� GLFWwindow, 2�� ����� ����������� ������� �������, 3�� �������� �������������� ��� ��������, 4�� ����� ����������� ������������ (shift, control, alt ��� super). ����� ����� ������ �������, GLFW ������� ��� ������� � �������� � ��� ��������� ���������.
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)								    // ����� ������������ ��������(�� ������)(GLFW_PRESS) ESC, ������������� �������� WindowShouldClose � true - � ���������� ����� ����� ���������
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if ((key >= 0) && (key < 1024))
    {
        if (action == GLFW_PRESS)
        {

            intilizaton.keys[key] = true;
        }
        else
        {
            if (action == GLFW_RELEASE)
            {

                intilizaton.keys[key] = false;
            }
        }
    }
}