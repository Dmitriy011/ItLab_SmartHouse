// GLEW нужно подключать до GLFW.
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
    if (intilizaton.GetFirstMouse())                            //изначально true
    {
        intilizaton.SetLastX(xpos);                             //последнее положение маши на экране по х
        intilizaton.SetLastY(ypos);                             //последнее положение маши на экране по у
        intilizaton.SetFirstMouse(false);                       
    }

    GLfloat xoffset = xpos - intilizaton.GetLastX();            //смещение мыши по х
    GLfloat yoffset = intilizaton.GetLastY() - ypos;            //смещение мыши по у

    intilizaton.SetLastX(xpos);                                 //устанавливаем последнее значение мыши по х
    intilizaton.SetLastY(ypos);                                 //устанавливаем последнее значение мыши по х

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)//Функция: 1аргумент указатель на GLFWwindow, 2ой число описывающее нажатую клавишу, 3ее действие осуществляемое над клавишей, 4ое число описывающее модификаторы (shift, control, alt или super). Когда будет нажата клавиша, GLFW вызовет эту функцию и передаст в нее требуемые аргументы.
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)								    // Когда пользователь НАЖИМАЕТ(не держит)(GLFW_PRESS) ESC, устанавливаем свойство WindowShouldClose в true - и приложение после этого закроется
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
