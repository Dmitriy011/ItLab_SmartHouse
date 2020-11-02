#pragma once

#include <vector>

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVTY = 0.25f;

enum Camera_Movement 
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    glm::vec3 Position;                                                                 //Позиция камеры
    glm::vec3 Front;                                                                    //vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f)
    glm::vec3 Up;                                                                       //Вектор вверх
    glm::vec3 Right;
    glm::vec3 WorldUp;
    GLfloat Yaw;                                                                        //угол
    GLfloat Pitch;                                                                      //угол
    GLfloat MovementSpeed;                                                              //Скорость движения камеры
    GLfloat MouseSensitivity;                                                           //Чувствительность

    //конструктор с углами, векторами, ...
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY)
    {
        this->Position = position;
        this->WorldUp = up;
        this->Yaw = yaw;
        this->Pitch = pitch;
        this->updateCameraVectors();
    }
    //констурктор со скалярами
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY)
    {
        this->Position = glm::vec3(posX, posY, posZ);
        this->WorldUp = glm::vec3(upX, upY, upZ);
        this->Yaw = yaw;
        this->Pitch = pitch;
        this->updateCameraVectors();
    }
    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);

    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
private:
    void updateCameraVectors();
};