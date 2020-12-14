#include "Intilization_value.h"

Intilization_value::Intilization_value()
{
	lightPos = glm::vec3(-2.0f, 0.0f, -1.5f);
	WIDTH = 800;												//размер окна
	HEIGHT = 600;													//размер окна
	lastX = 400;
	lastY = 300;
	firstMouse = true;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
}

glm::vec3 Intilization_value::GetlightPos()
{
	return lightPos;
}

GLuint Intilization_value::GetWidht()
{
	return WIDTH;
}

GLuint Intilization_value::GetHeight()
{
	return HEIGHT;
}
