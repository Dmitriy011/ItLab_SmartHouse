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
    //����������� � ������, ���������, ...
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

    mat4 GetProjectionMatrix() const;                                                                                                                       //�������� ������� ��������
    mat4 GetViewMatrix() const;                                                                                                                             //�������� ������� ���� LookAt
    vec3 GetPosition() const;                                                                                                                               //�������� ������� ������
    vec3 GetFront() const;                                                                                                                                  //�������� ������, ������������ ������
    vec3 GetUp() const;                                                                                                                                     //�������� ������, ������������ �����
    vec3 GetRight() const;                                                                                                                                  //�������� ������, ������������ ������
    vec3 GetWorldUp() const;                                                                                                                                //
    GLfloat GetYaw() const;                                                                                                                                 //�������� yaw(��������): ���� ������:��� �������� ��������
    GLfloat GetPitch() const;                                                                                                                               //�������� pitch(������): ���� ������:��� �������� ��������
    GLfloat GetMovementSpeed() const;                                                                                                                       //�������� �������� �������� ������
    GLfloat GetMouseSensitivity() const;                                                                                                                    //�������� �������� �������� ����

private:
    mat4 viewMatrix;
    mat4 projectionMatrix;

    vec3 Position;                                                                 //������� ������
    vec3 Front;                                                                    //vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f)
    vec3 Up;                                                                       //������ �����
    vec3 Right;
    vec3 WorldUp;
    GLfloat Yaw;                                                                   //����
    GLfloat Pitch;                                                                 //����
    GLfloat MovementSpeed;                                                         //�������� �������� ������
    GLfloat MouseSensitivity;                                                      //����������������
 
    void updateCameraVectors();
};
