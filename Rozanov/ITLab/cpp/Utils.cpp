// GLEW ����� ���������� �� GLFW.
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include <iostream>

#include "Utils.h"
#include "Intilization.h"


void Utils::movement(Intilization intilizaton)
{
    if (intilizaton.keys[GLFW_KEY_W])
    {
        camera.ProcessKeyboard(FORWARD, intilizaton.GetDeltaTime());
    }
    if (intilizaton.keys[GLFW_KEY_S])
    {
        camera.ProcessKeyboard(BACKWARD, intilizaton.GetDeltaTime());
    }
    if (intilizaton.keys[GLFW_KEY_A])
    {
        camera.ProcessKeyboard(LEFT, intilizaton.GetDeltaTime());
    }
    if (intilizaton.keys[GLFW_KEY_D])
    {
        camera.ProcessKeyboard(RIGHT, intilizaton.GetDeltaTime());
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (intilizaton.GetFirstMouse())                            //���������� true
    {
        intilizaton.SetLastX(xpos);                             //��������� ��������� ���� �� ������ �� �
        intilizaton.SetLastY(ypos);                             //��������� ��������� ���� �� ������ �� �
        intilizaton.SetFirstMouse(false);                       
    }

    GLfloat xoffset = xpos - intilizaton.GetLastX();            //�������� ���� �� �
    GLfloat yoffset = intilizaton.GetLastY() - ypos;            //�������� ���� �� �

    intilizaton.SetLastX(xpos);                                 //������������� ��������� �������� ���� �� �
    intilizaton.SetLastY(ypos);                                 //������������� ��������� �������� ���� �� �

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
