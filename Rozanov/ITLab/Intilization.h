#pragma once

#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Intilization
{
public:
	bool keys[1024];
	//----// ��� ������ ���������� �������� ������������ ������ -> ������ ����� ����������� �� ������������ � �� ���� ������� ��������
	GLfloat deltaTime;															// �����, ����������� �� ������������ ���������� ����������� �����
	GLfloat lastFrame;															// ����� ������ ���������� �����
	GLfloat lastX;
	GLfloat	lastY;
	bool firstMouse;

	Intilization();

	void intilization_libs();

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