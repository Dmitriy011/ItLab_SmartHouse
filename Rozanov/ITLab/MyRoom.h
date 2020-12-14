#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glew.h>
#include <glfw3.h>

#include <SOIL.h>

float vertices[] =
{
	// positions          // normals          // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

GLuint indices[] =
{
	0, 1, 3,																	// 1�� �����������
	1, 2, 3																		// 2�� �����������
};

class MyRoom
{
public:
	GLuint  VBO, objectVAO, EBO;
	GLuint lightVAO;
	GLuint diffuseMap;																				//6)�������� �������	

	void create_RoomAndLight()
	{
		
		glGenBuffers(1, &VBO);															//������� VBO ����� ��� �������,											
		glGenVertexArrays(1, &objectVAO);														//VAO
		glGenBuffers(1, &EBO);															//EBO
		glBindVertexArray(objectVAO);															//������ VAO(-> ���������� �������� VBO � ��������� �� �������� � VAO)
		glBindBuffer(GL_ARRAY_BUFFER, VBO);												//4)��� ������, ������� ����� ������� VBO ����� � ������ GL_ARRAY_BUFFER(������ ����� GL_ARRAY_BUFFER. ������ ����� �����, ������������ �����, ����� �������� � VBO.) (GL_ELEMENT_ARRAY_BUFFER ������������ ��� ����������� ������, �������)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);										//4)(GL_ELEMENT_ARRAY_BUFFER ������������ ��� ����������� ������, ������� �������� ������� ������� �������� � ������ GL_ARRAY_BUFFER)
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		//4)�������� ���� ������� � ����� ��� OpenGL.����� glBufferData ��� ����������� ��������� ������ � ���� �����(����������� ������ ������������ � ��������� �����).1�������� �  ��� ������ � ������� �� ����� ����������� ������ (��� VBO ������ �������� � GL_ARRAY_BUFFER). 2�� - ���������� ���������� ������ (� ������), ������� ����� �������� ������. 3 �������� � ���  ������. 4�������� ���������� ��� �� ����� ����� ���������� �������� � ����������� �� �������(3 ������:GL_STATIC_DRAW: ������ ���� ������� �� ����� ����������(������ � ������� ������������ �������� �� �����), ���� ����� ���������� ����� �����; GL_DYNAMIC_DRAW: ������ ����� �������� �������� �����;GL_STREAM_DRAW: ������ ����� �������� ��� ������ ���������) (������ ��� ����������)). 
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//4)�������� ������� ������ 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);						//5)������� ��� ������: ������������� ��������� �� ��������� ��������. 1-�� �������� - ����� �������� ������� ����� ���������(position - layout (location = 0)), 2�� �������� -  ������ ���������(�.�. vec3), 3��  ������������ ��� ������, 4�� ��������� ������������� ������������� ������� ������(���� ������ GL_TRUE, �� ��� ������ ����� ����������� ����� 0 (-1 ��� �������� ��������) � 1. ������������ �� ��������� -> ��������� GL_FALSE), 5�� ���(��������� ���������� ����� �������� ������), 6�� - ����� ��� GLvoid*-> ���������� ���������� �����. - ��� �������� ������ ������ � ������(� ��� ����� �� ����� �������� � �������  ��������� 0)
		glEnableVertexAttribArray(0);																			//5)�.� ������� ������ �������� -> ��������
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));	//5)������� �����:
		glEnableVertexAttribArray(1);																			//5)���
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));	//5)������� ������������ ��������
		glEnableVertexAttribArray(2);																			//5)���					
		glBindVertexArray(0);																					//���������� Vao (����� ����� ����� ��������� "glBindVertexArray(VAO);" � ����� ����� ��������)
	
		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(lightVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);																			
		// Texture 1
		glGenTextures(1, &diffuseMap);																	//6)�������� �������� (1�� ��� - ����������� �������, 2�� - ������ ��������������� �������)
		glBindTexture(GL_TEXTURE_2D, diffuseMap);															//������
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);									//1�� ��� - � ���� �������� ��������(2� - GL_TEXTURE_2D), 2�� ��� - ����� ��������(WRAP)(WRAP_S - ��� ��� S), 3�� - ����� wrapping(GL_MIRRORED_REPEAT)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);									//WRAP_T - ��� ��� T
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int width, height;
		unsigned char* image = SOIL_load_image("../Pics/floor.jpg", &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);		//1�� - ���������� ����(GL_TEXTURE_2D), 2�� - ��������� ������� ������� ��� �������� �� ����� ������������� ��������(0 - ��������� �� OPENGL),	3�� - ����� ������� ������� ��������, 4�� - ������, 5�� - ������, 6�� - ����������(����� 0), 7�� - ������ �������(RGB), 8�� - ��� ������ �����������(�.�. ��������� ����������� � ������� � ������ (cha)r - GL_UNSIGNED_BYTE), 9�� - �����������
		glGenerateMipmap(GL_TEXTURE_2D);																//��������� ��������
		SOIL_free_image_data(image);																	//�������� ��.������ ��� �������	
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	~MyRoom()
	{
		glDeleteVertexArrays(1, &objectVAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	
private:
};