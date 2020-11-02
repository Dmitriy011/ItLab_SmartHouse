// GLEW нужно подключать до GLFW.
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include <iostream>

#include "SomeFunc.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)	//Функция: 1аргумент указатель на GLFWwindow, 2ой число описывающее нажатую клавишу, 3ее действие осуществляемое над клавишей, 4ое число описывающее модификаторы (shift, control, alt или super). Когда будет нажата клавиша, GLFW вызовет эту функцию и передаст в нее требуемые аргументы.
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)								// Когда пользователь НАЖИМАЕТ(не держит)(GLFW_PRESS) ESC, устанавливаем свойство WindowShouldClose в true - и приложение после этого закроется
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

    if ((key >= 0) && (key < 1024))
    {
        if (action == GLFW_PRESS)
        {

            keys[key] = true;
        }
        else
        {
            if (action == GLFW_RELEASE)
            {

                keys[key] = false;
            }
        }
    }
}

void movement()
{
    if (keys[GLFW_KEY_W])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (keys[GLFW_KEY_S])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (keys[GLFW_KEY_A])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (keys[GLFW_KEY_D])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)                   //xpos, ypos - коорд мыши.
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;  

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
