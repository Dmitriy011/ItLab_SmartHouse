// GLEW ����� ���������� �� GLFW.
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SomeFunc.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Mesh.h"


#include <iostream>

#include <SOIL.h>

const GLuint WIDTH = 800, HEIGHT = 600;												//������ ����

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

//----// ��� ������ ���������� �������� ������������ ������ -> ������ ����� ����������� �� ������������ � �� ���� ������� ��������
GLfloat deltaTime = 0.0f;															// �����, ����������� �� ������������ ���������� ����������� �����
GLfloat lastFrame = 0.0f;															// ����� ������ ���������� �����


int main(int argc, char** argv)														//argc ����� ����������, argv ������ ����������
{

	//������������� GLFW. ��������� GLFW
	glfwInit();	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);									//glfwWindowHint(<������������� ���������, ������� ������������ ���������>, <��������, ������� ��������������� ���������������� ���������>).GLFW_CONTEXT_VERSION_MAJOR � GLFW_CONTEXT_VERSION_MINOR ��������� ������ ����������� API(������������ ���������� ����������), � ������� ������ ���� ��������� ��������� ��������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);					//GLFW_OPENGL_PROFILE ���������, ��� ������ ������� OpenGL ������� ��������.(GLFW_OPENGL_CORE_PROFILE ��� GLFW_OPENGL_COMPAT_PROFILE ��� GLFW_OPENGL_ANY_PROFILE, ����� �� ����������� ���������� �������. ���� ������������� ������ OpenGL ���� 3.2, ���������� ������������ GLFW_OPENGL_ANY_PROFIL)
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);										//���������� ����������� ��������� ������� ����

	GLFWwindow* window = glfwCreateWindow(800, 600, "Room1", nullptr, nullptr);		//������, ������. ���������� ��������� �� ������ ���� GLFWwindow
	if (window == nullptr)															//�������� �� ��������
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();															//�������� ��������		
		return -1;
	}
	glfwMakeContextCurrent(window);													//������ ��� �� ������ ������������ ������� ��� ������������ � ��������� ���� ��� ����� ������� ��� ������� ����������

	glViewport(0, 0, WIDTH, HEIGHT);												//�������� Opengl ������ ���� - glViewport(<������� ������� ������ ���� ������1>, <������� ������� ������ ���� ������2>, <������>, <������>);
	//��������, ��� ��������������.
	if (glewInit() != GLEW_OK)
	{
		return 1;
	}
	glewInit();																		//�������������� ����� �������� �������� ��������� glfwMakeContextCurrent 

	glEnable(GL_DEPTH_TEST);														//���, ����� OpenGL  �������� �������� �������, ������� �������� �������� GL_DEPTH_TEST	

	glfwSetKeyCallback(window, key_callback);										//�������� ���-�� �-�� � GLWF

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);					//������ ������� ���� ��� ����.

	glfwSetCursorPosCallback(window, mouse_callback);								//�������� ���-�� �-�� � GLWF

	Shader ourShader("../Shader/Vertex/Vertex.txt", "../Shader/Fragment/fragment.txt ");

	float vertices[] = 
	{
	-4.5f, 0.0f, -2.75f,  0.0f, 0.0f,	//1��
	 4.5f, 0.0f, -2.75f,  1.0f, 0.0f,
	 4.5f,  2.5f, -2.75f,  1.0f, 1.0f,
	 4.5f,  2.5f, -2.75f,  1.0f, 1.0f,	//2��
	-4.5f,  2.5f, -2.75f,  0.0f, 1.0f,
	-4.5f, 0.0f, -2.75f,  0.0f, 0.0f,

	-4.5f, 0.0f,  2.75f,  0.0f, 0.0f,	//1��
	 4.5f, 0.0f,  2.75f,  1.0f, 0.0f,
	 4.5f,  2.5f,  2.75f,  1.0f, 1.0f,
	 4.5f,  2.5f,  2.75f,  1.0f, 1.0f,	//2��
	-4.5f,  2.5f,  2.75f,  0.0f, 1.0f,
	-4.5f, 0.0f,  2.75f,  0.0f, 0.0f,

	-4.5f,  2.5f,  2.75f,  1.0f, 0.0f,	//1��
	-4.5f,  2.5f, -2.75f,  1.0f, 1.0f,
	-4.5f, 0.0f, -2.75f,  0.0f, 1.0f,
	-4.5f, 0.0f, -2.75f,  0.0f, 1.0f,	//2��
	-4.5f, 0.0f,  2.75f,  0.0f, 0.0f,
	-4.5f,  2.5f,  2.75f,  1.0f, 0.0f,

	 4.5f,  2.5f,  2.75f,  1.0f, 0.0f,	//1��
	 4.5f,  2.5f, -2.75f,  1.0f, 1.0f,
	 4.5f, 0.0f, -2.75f,  0.0f, 1.0f,
	 4.5f, 0.0f, -2.75f,  0.0f, 1.0f,	//2��		
	 4.5f, 0.0f,  2.75f,  0.0f, 0.0f,
	 4.5f,  2.5f,  2.75f,  1.0f, 0.0f,

	-4.5f, 0.0f, -2.75f,  0.0f, 1.0f,	//1��
	 4.5f, 0.0f, -2.75f,  1.0f, 1.0f,
	 4.5f, 0.0f,  2.75f,  1.0f, 0.0f,
	 4.5f, 0.0f,  2.75f,  1.0f, 0.0f,	//2��
	-4.5f, 0.0f,  2.75f,  0.0f, 0.0f,
	-4.5f, 0.0f, -2.75f,  0.0f, 1.0f,
	};

	GLuint indices[] =
	{  
		0, 1, 3,																	// 1�� �����������
		1, 2, 3																		// 2�� �����������
	};

	//�������� VBO, VAO, EBO
	GLuint  VBO, VAO, EBO;
	//----//																		 
	glGenBuffers(1, &VBO);															//������� VBO ����� ��� �������,											
	glGenVertexArrays(1, &VAO);														//VAO
	glGenBuffers(1, &EBO);															//EBO
	//----//
	glBindVertexArray(VAO);															//������ VAO(-> ���������� �������� VBO � ��������� �� �������� � VAO)
	//----//
	glBindBuffer(GL_ARRAY_BUFFER, VBO);												//4)��� ������, ������� ����� ������� VBO ����� � ������ GL_ARRAY_BUFFER(������ ����� GL_ARRAY_BUFFER. ������ ����� �����, ������������ �����, ����� �������� � VBO.) (GL_ELEMENT_ARRAY_BUFFER ������������ ��� ����������� ������, �������)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);										//4)(GL_ELEMENT_ARRAY_BUFFER ������������ ��� ����������� ������, ������� �������� ������� ������� �������� � ������ GL_ARRAY_BUFFER)
	//----//
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		//4)�������� ���� ������� � ����� ��� OpenGL.����� glBufferData ��� ����������� ��������� ������ � ���� �����(����������� ������ ������������ � ��������� �����).1�������� �  ��� ������ � ������� �� ����� ����������� ������ (��� VBO ������ �������� � GL_ARRAY_BUFFER). 2�� - ���������� ���������� ������ (� ������), ������� ����� �������� ������. 3 �������� � ���  ������. 4�������� ���������� ��� �� ����� ����� ���������� �������� � ����������� �� �������(3 ������:GL_STATIC_DRAW: ������ ���� ������� �� ����� ����������(������ � ������� ������������ �������� �� �����), ���� ����� ���������� ����� �����; GL_DYNAMIC_DRAW: ������ ����� �������� �������� �����;GL_STREAM_DRAW: ������ ����� �������� ��� ������ ���������) (������ ��� ����������)). 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//4)�������� ������� ������ 
	//----//
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);						//5)������� ��� ������: ������������� ��������� �� ��������� ��������. 1-�� �������� - ����� �������� ������� ����� ���������(position - layout (location = 0)), 2�� �������� -  ������ ���������(�.�. vec3), 3��  ������������ ��� ������, 4�� ��������� ������������� ������������� ������� ������(���� ������ GL_TRUE, �� ��� ������ ����� ����������� ����� 0 (-1 ��� �������� ��������) � 1. ������������ �� ��������� -> ��������� GL_FALSE), 5�� ���(��������� ���������� ����� �������� ������), 6�� - ����� ��� GLvoid*-> ���������� ���������� �����. - ��� �������� ������ ������ � ������(� ��� ����� �� ����� �������� � �������  ��������� 0)
	glEnableVertexAttribArray(0);																			//5)�.� ������� ������ �������� -> ��������
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));	//5)������� �����:
	glEnableVertexAttribArray(1);																			//5)���
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));	//5)������� ������������ ��������
	glEnableVertexAttribArray(2);																			//5)���					
	glBindVertexArray(0);															//���������� Vao (����� ����� ����� ��������� "glBindVertexArray(VAO);" � ����� ����� ��������) 												
	
	
	GLuint texture1;																				//6)�������� �������																				
	// Texture 1
	glGenTextures(1, &texture1);																	//6)�������� �������� (1�� ��� - ����������� �������, 2�� - ������ ��������������� �������)
	glBindTexture(GL_TEXTURE_2D, texture1);															//������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);									//1�� ��� - � ���� �������� ��������(2� - GL_TEXTURE_2D), 2�� ��� - ����� ��������(WRAP)(WRAP_S - ��� ��� S), 3�� - ����� wrapping(GL_MIRRORED_REPEAT)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);									//WRAP_T - ��� ��� T
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("../Pics/floor.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);		//1�� - ���������� ����(GL_TEXTURE_2D), 2�� - ��������� ������� ������� ��� �������� �� ����� ������������� ��������(0 - ��������� �� OPENGL),	3�� - ����� ������� ������� ��������, 4�� - ������, 5�� - ������, 6�� - ����������(����� 0), 7�� - ������ �������(RGB), 8�� - ��� ������ �����������(�.�. ��������� ����������� � ������� � ������ (cha)r - GL_UNSIGNED_BYTE), 9�� - �����������
	glGenerateMipmap(GL_TEXTURE_2D);																//��������� ��������
	SOIL_free_image_data(image);																	//�������� ��.������ ��� �������	
	glBindTexture(GL_TEXTURE_2D, 0);																//������� ������� ��������	
	

	Model Table(const_cast<GLchar*>("../Models/Table/Wood_Table.obj"));
	Model Door(const_cast<GLchar*>("../Models/Room-door/Door_Component_BI3.obj"));
	//Model Tree(const_cast<GLchar*>("../Models/Tree/Tree.obj"));
	Model Ref(const_cast<GLchar*>("../Models/refregerator/Refrigerator.obj"));
	//Model Ta(const_cast<GLchar*>("../Models/table2/table3.obj"));
	Model lamp(const_cast<GLchar*>("../Models/lamp/eb_lamp_01.obj"));

	while (!glfwWindowShouldClose(window))											//���������, �� �������� �� �������� ��������� ������ 
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();															//��������� ������� � �������� ������� ��������� ������(����� ����� � ���������� ��� ����������� ����) � �������� ������������� �������
		movement();
		glBindVertexArray(VAO);														//��� Vao	

	//������� ��������� ...
		glClearColor(0.5f, 0.3f, 1.0f, 1.0f);										//���� ����
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);							//GlClear(<����� ���� ��������>) - �������� ����� (GL_COLOR_BUFFER_BIT - ��������,  GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT )��� ������ �� �������� glClear ���� ����� ����� �������� ��������� 	������.glClearColor � ��� ������� ��������������� ���������, � glClear � ��� ������� ������������ ���������
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);

		ourShader.Use();
		
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, .0f, 0.0f));				//��������� ������� ������, ����� ���������� ����������� � ���� ����������, �������� �� 55 ��������, �������� � �������� �������� �� (1, 0, 0)														//������� ������ (������� �� �������, ���������������, ���������) ->����������. ��� ��������� ������� ������� � ���������� ������� ������������
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");			//1)�������� ������� ������ � ������
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glm::mat4 view = camera.GetViewMatrix();									//������� ������ (��������� �������������� ������� ��������� � ����������, ������� ��������, ��� ����� ������������ ������� �� ��� �������)
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");			//2)�������� ������� ���� � ������
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glm::mat4 projection;														//������� ��������
		projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);	//������������ �������� (���. �������������, � ������� ��������� �������� �� ������� ����� - ��� ��� 2�). 1�� ��� - fov (���� ������) 45 ��������
		GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");		//3)�������� ������� �������� � ������
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glDrawArrays(GL_TRIANGLES, 0, 30);										//��������� �������� �������� GL_TRIANGLES. 2�� �������� - ��� ������ �������  ������, 3�� ���������� ������
	
		model = glm::translate(model, glm::vec3(4.5f, 0.0f, 0.0f));				 		
		model = glm::rotate(model, 270.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		modelLoc = glGetUniformLocation(ourShader.Program, "model");			
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Door.Draw(ourShader);
		
		model = glm::translate(model, glm::vec3(2.2f, 0.7f, 8.5f));				
		model = glm::rotate(model, 130.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		modelLoc = glGetUniformLocation(ourShader.Program, "model");			
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ref.Draw(ourShader);
		
		model = glm::translate(model, glm::vec3(2.1f, -0.7f, -2.5f));
		model = glm::scale(model, glm::vec3(0.015, 0.015, 0.015));
		modelLoc = glGetUniformLocation(ourShader.Program, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		lamp.Draw(ourShader);

		

		glBindVertexArray(0);													//���������� VAO
	//�����.

		glfwSwapBuffers(window);												//�������� �������� �����, ������� ������������� ��� ��������� �� ����� ������� �������� � ���������� ��������� �� ������.
	}
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();															//*�������� ���������� ��������
	return 0;
}

