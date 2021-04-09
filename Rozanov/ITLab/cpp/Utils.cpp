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

unsigned int Utils::loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = SOIL_load_image(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        SOIL_free_image_data(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        SOIL_free_image_data(data);
    }

    return textureID;
}

unsigned int Utils::loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = SOIL_load_image(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            SOIL_free_image_data(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            SOIL_free_image_data(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
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
