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

void brighness(Shader& shader)
{
    string filename = "../test/test.txt";
    ifstream fin;
    fin.open(filename);
    if (fin.is_open())
    {
        fin.seekg(-1, ios_base::end);

        bool tmp = true;
        while (tmp)
        {
            char ch;
            fin.get(ch);

            if ((int)fin.tellg() <= 1)
            {
                fin.seekg(0);
                tmp = false;
            }
            else
            {
                if (ch == '\n')
                {
                    tmp = false;
                }
                else
                {
                    fin.seekg(-2, ios_base::cur);
                }
            }

        }
    }
        string lastLine;
        getline(fin, lastLine);

        string temp;

        if (lastLine.find_last_of(';') == 18)
        {
            temp.push_back(lastLine[16]);
            temp.push_back(lastLine[17]);
            cout << temp;
        }
        if (lastLine.find_last_of(';') == 17)
        {
            temp.push_back(lastLine[16]);
            cout << temp;
        }
        
        switch (stoi(temp))
        {
        case 0:
        {
            shader.setFloat("light.constant", 1.0f);
            shader.setFloat("light.linear", 0.7f);
            shader.setFloat("light.quadratic", 1.8f);
            break;
        }
        case 1:
        {   
            shader.setFloat("light.constant", 1.0f);
            shader.setFloat("light.linear", 0.35f);
            shader.setFloat("light.quadratic", 0.44f);
            break;
        }
        case 2:
        {
            shader.setFloat("light.constant", 1.0f);
            shader.setFloat("light.linear", 0.22f);
            shader.setFloat("light.quadratic", 0.20f);
            break;
        }
        case 3:
        {
            shader.setFloat("light.constant", 1.0f);
            shader.setFloat("light.linear", 0.14f);
            shader.setFloat("light.quadratic", 0.07f);
            break;
        }
        case 4:
        {
            shader.setFloat("light.constant", 1.0f);
            shader.setFloat("light.linear", 0.09f);
            shader.setFloat("light.quadratic", 0.032f);
            break;
        }
        case 5:
        {
            shader.setFloat("light.constant", 1.0f);
            shader.setFloat("light.linear", 0.07f);
            shader.setFloat("light.quadratic", 0.017f);
            break;
        }
        case 6:
        {
            shader.setFloat("light.constant", 1.0f);
            shader.setFloat("light.linear", 0.045f);
            shader.setFloat("light.quadratic", 0.0075f);
            break;
        }
        case 7:
        {
            shader.setFloat("light.constant", 1.0f);
            shader.setFloat("light.linear", 0.027f);
            shader.setFloat("light.quadratic", 0.0028f);
            break;
        }
        case 8:
        {
            shader.setFloat("light.constant", 1.0f);
            shader.setFloat("light.linear", 0.022f);
            shader.setFloat("light.quadratic", 0.0019f);
            break;
        }
        case 9:
        {
            shader.setFloat("light.constant", 1.0f);
            shader.setFloat("light.linear", 0.014f);
            shader.setFloat("light.quadratic", 0.0007f);
            break;
        }
        case 10:
        {
            shader.setFloat("light.constant", 1.0f);
            shader.setFloat("light.linear", 0.007f);
            shader.setFloat("light.quadratic", 0.0002f);
            break;
        }
        case 11:
        {
            shader.setFloat("light.constant", 1.0f);
            shader.setFloat("light.linear", 0.0014f);
            shader.setFloat("light.quadratic", 0.000007f);
            break;
        }
    }
}
