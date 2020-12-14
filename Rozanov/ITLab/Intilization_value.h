#pragma once

#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Intilization_value
{
public:
	bool keys[1024];
	//----// ��� ������ ���������� �������� ������������ ������ -> ������ ����� ����������� �� ������������ � �� ���� ������� ��������
	GLfloat deltaTime;															// �����, ����������� �� ������������ ���������� ����������� �����
	GLfloat lastFrame;															// ����� ������ ���������� �����
	GLfloat lastX;
	GLfloat	lastY;
	bool firstMouse;

	Intilization_value();

	void intilization_libs()
	{
		//������������� GLFW. ��������� GLFW
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);									//glfwWindowHint(<������������� ���������, ������� ������������ ���������>, <��������, ������� ��������������� ���������������� ���������>).GLFW_CONTEXT_VERSION_MAJOR � GLFW_CONTEXT_VERSION_MINOR ��������� ������ ����������� API(������������ ���������� ����������), � ������� ������ ���� ��������� ��������� ��������
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);					//GLFW_OPENGL_PROFILE ���������, ��� ������ ������� OpenGL ������� ��������.(GLFW_OPENGL_CORE_PROFILE ��� GLFW_OPENGL_COMPAT_PROFILE ��� GLFW_OPENGL_ANY_PROFILE, ����� �� ����������� ���������� �������. ���� ������������� ������ OpenGL ���� 3.2, ���������� ������������ GLFW_OPENGL_ANY_PROFIL)
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glViewport(0, 0, WIDTH, HEIGHT);												//�������� Opengl ������ ���� - glViewport(<������� ������� ������ ���� ������1>, <������� ������� ������ ���� ������2>, <������>, <������>);
	}

	int intilization_glew()
	{
		//��������, ��� ��������������.
		if (glewInit() != GLEW_OK)
		{
			return 1;
		}
		glewInit();																		//�������������� ����� �������� �������� ��������� glfwMakeContextCurrent 
	}

	void settings()
	{
		glEnable(GL_DEPTH_TEST);														//���, ����� OpenGL  �������� �������� �������, ������� �������� �������� GL_DEPTH_TEST	
	}

	glm::vec3 GetlightPos();
	GLuint GetWidht();
	GLuint GetHeight();
	
private:
	glm::vec3 lightPos;
	GLuint WIDTH;
	GLuint HEIGHT;
};