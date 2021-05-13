#pragma once

#include <vector>

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

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
    //конструктор с углами, векторами, ...
    Camera(vec3 position = vec3(0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = -90.0f, GLfloat pitch = 0.0f) : Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(3.0), MouseSensitivity(0.25f)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);

    mat4 GetProjectionMatrix() const;                                                                                                                       //получить матрицу проекции
    mat4 GetViewMatrix() const;                                                                                                                             //получить матрицы вида LookAt
    vec3 GetPosition() const;                                                                                                                               //получить позицию камеры
    vec3 GetFront() const;                                                                                                                                  //получить вектор, направленный вперед
    vec3 GetUp() const;                                                                                                                                     //получить вектор, направленный вверх
    vec3 GetRight() const;                                                                                                                                  //получить вектор, направленный вправо
    vec3 GetWorldUp() const;                                                                                                                                //
    GLfloat GetYaw() const;                                                                                                                                 //получить yaw(рыскание): угол Эйлера:для описания вращения
    GLfloat GetPitch() const;                                                                                                                               //получить pitch(тангаж): угол Эйлера:для описания вращения
    GLfloat GetMovementSpeed() const;                                                                                                                       //получить скорость движения камеры
    GLfloat GetMouseSensitivity() const;                                                                                                                    //получить скорость движения мыши

private:
    mat4 viewMatrix;
    mat4 projectionMatrix;

    vec3 Position;                                                                 //Позиция камеры
    vec3 Front;                                                                    //vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f)
    vec3 Up;                                                                       //Вектор вверх
    vec3 Right;
    vec3 WorldUp;
    GLfloat Yaw;                                                                   //угол
    GLfloat Pitch;                                                                 //угол
    GLfloat MovementSpeed;                                                         //Скорость движения камеры
    GLfloat MouseSensitivity;                                                      //Чувствительность
 
    void updateCameraVectors();
};
