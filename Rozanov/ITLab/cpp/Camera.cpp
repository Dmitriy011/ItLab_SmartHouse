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
    xoffset *= MouseSensitivity;                                    //умножаем значение смещения мыши на sensivity по х
    yoffset *= MouseSensitivity;                                    //умножаем значение смещения мыши на sensivity по у

    Yaw += xoffset;                                                 //смещение для угла yaw
    Pitch += yoffset;                                               //смещение для угла pitch

    //ограничения для угла поврота pitch (по y). предел +-89ю0, т.к. ф>90 cosф < 0 -> сможем смотреть вниз и вверх, но не более
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
    //ограничвать угол по х нет необх.

    updateCameraVectors();                                          //обновление на новые значения векторов камеры
}

mat4 Camera::GetViewMatrix() const
{
    return lookAt(Position, Position + Front, Up);                        //lookAt - матрица вида. Для ее создания необходимо знать позицию камеры, вектор направления камеры и вектор направленный вверх
}

mat4 Camera::GetProjectionMatrix() const
{
    return projectionMatrix;                                             //матрица проекции: учитывает угол поля зрения
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
    //формирование вектора Front
    vec3 front;
    front.x = cos(radians(Yaw)) * cos(radians(Pitch));
    front.y = sin(radians(Pitch));
    front.z = sin(radians(Yaw)) * cos(radians(Pitch));                         

    Front = normalize(front);                                                   //инициализация нового вектора, направленного верх :
    Right = normalize(cross(Front, WorldUp));                                   //инициализация нового вектора, направленного вправо:cross - векторное произведение
    Up = normalize(cross(Right, Front));                                        //инициализация нового вектора, направленного верх: cross - векторное произведение
}
