#include "Intilization.h"

Intilization::Intilization()
{
	WIDTH = 800;												//������ ����
	HEIGHT = 600;												//������ ����
	lastX = 400;
	lastY = 300;
	firstMouse = true;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
}

void Intilization::intilization_libs()
{
	//������������� GLFW. ��������� GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);									//glfwWindowHint(<������������� ���������, ������� ������������ ���������>, <��������, ������� ��������������� ���������������� ���������>).GLFW_CONTEXT_VERSION_MAJOR � GLFW_CONTEXT_VERSION_MINOR ��������� ������ ����������� API(������������ ���������� ����������), � ������� ������ ���� ��������� ��������� ��������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);					//GLFW_OPENGL_PROFILE ���������, ��� ������ ������� OpenGL ������� ��������.(GLFW_OPENGL_CORE_PROFILE ��� GLFW_OPENGL_COMPAT_PROFILE ��� GLFW_OPENGL_ANY_PROFILE, ����� �� ����������� ���������� �������. ���� ������������� ������ OpenGL ���� 3.2, ���������� ������������ GLFW_OPENGL_ANY_PROFIL)
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glViewport(0, 0, WIDTH, HEIGHT);												//�������� Opengl ������ ���� - glViewport(<������� ������� ������ ���� ������1>, <������� ������� ������ ���� ������2>, <������>, <������>);

}

int Intilization::intilization_glew()
{
	//��������, ��� ��������������.
	if (glewInit() != GLEW_OK)
	{
		return 1;
	}
	glewInit();																		//�������������� ����� �������� �������� ��������� glfwMakeContextCurrent 
}

void Intilization::settings()
{
	glEnable(GL_DEPTH_TEST);														//���, ����� OpenGL  �������� �������� �������, ������� �������� �������� GL_DEPTH_TEST	
}

GLuint Intilization::GetWidht() const
{
	return WIDTH;
}

GLuint Intilization::GetHeight() const
{
	return HEIGHT;
}

GLfloat Intilization::GetDeltaTime() const
{
	return deltaTime;
}

GLfloat Intilization::GetLastFrame() const
{
	return lastFrame;
}

GLfloat Intilization::GetLastX() const
{
	return lastX;
}

GLfloat Intilization::GetLastY() const
{
	return lastY;
}

bool Intilization::GetFirstMouse() const
{
	return firstMouse;
}

void Intilization::SetDeltaTime(GLfloat _v)
{
	deltaTime = _v;
}

void Intilization::SetLastFrame(GLfloat _v)
{
	lastFrame = _v;
}

void Intilization::SetLastX(GLfloat _v)
{
	lastX = _v;
}

void Intilization::SetLastY(GLfloat _v)
{
	lastY = _v;
}

void Intilization::SetFirstMouse(bool _v)
{
	firstMouse = _v;
}
