#include "Camera.h"

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
    GLfloat velocity = MovementSpeed * deltaTime;

    if (direction == FORWARD)
    {
        Position += Front * velocity;
    }
    if (direction == BACKWARD)
    {
        Position -= Front * velocity;
    }
    if (direction == LEFT)
    {
        Position -= Right * velocity;
    }
    if (direction == RIGHT)
    {
        Position += Right * velocity;
    }

    Position.y = 0.35f;
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;                                    //�������� �������� �������� ���� �� sensivity �� �
    yoffset *= MouseSensitivity;                                    //�������� �������� �������� ���� �� sensivity �� �

    Yaw += xoffset;                                                 //�������� ��� ���� yaw
    Pitch += yoffset;                                               //�������� ��� ���� pitch

    //����������� ��� ���� ������� pitch (�� y). ������ +-89�0, �.�. �>90 cos� < 0 -> ������ �������� ���� � �����, �� �� �����
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
        {
            Pitch = 89.0f;
        }
        if (Pitch < -89.0f)
        {
            Pitch = -89.0f;
        }
    }
    //����������� ���� �� � ��� �����.

    updateCameraVectors();                                          //���������� �� ����� �������� �������� ������
}

mat4 Camera::GetViewMatrix() const
{
    return lookAt(Position, Position + Front, Up);                        //lookAt - ������� ����. ��� �� �������� ���������� ����� ������� ������, ������ ����������� ������ � ������ ������������ �����
}

mat4 Camera::GetProjectionMatrix() const
{
    return projectionMatrix;                                             //������� ��������: ��������� ���� ���� ������
}

vec3 Camera::GetPosition() const
{
    return Position;
}

vec3 Camera::GetFront() const
{
    return Front;
}

vec3 Camera::GetUp() const
{
    return Up;
}

vec3 Camera::GetRight() const
{
    return Right;
}

vec3 Camera::GetWorldUp() const
{
    return WorldUp;
}

GLfloat Camera::GetYaw() const
{
    return Yaw;
}

GLfloat Camera::GetPitch() const
{
    return Pitch;
}

GLfloat Camera::GetMovementSpeed() const
{
    return MovementSpeed;
}

GLfloat Camera::GetMouseSensitivity() const
{
    return MouseSensitivity;
}

void Camera::updateCameraVectors()
{
    //������������ ������� Front
    vec3 front;
    front.x = cos(radians(Yaw)) * cos(radians(Pitch));
    front.y = sin(radians(Pitch));
    front.z = sin(radians(Yaw)) * cos(radians(Pitch));                         

    Front = normalize(front);                                                   //������������� ������ �������, ������������� ���� :
    Right = normalize(cross(Front, WorldUp));                                   //������������� ������ �������, ������������� ������:cross - ��������� ������������
    Up = normalize(cross(Right, Front));                                        //������������� ������ �������, ������������� ����: cross - ��������� ������������
}
