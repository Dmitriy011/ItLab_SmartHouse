// GLEW ����� ���������� �� GLFW.
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include <iostream>

#include "SomeFunc.h"
	
const GLuint WIDTH = 800, HEIGHT = 600;												//������ ����

//�������� ��� ���������� ������� (������������ ��� ��������� ������)
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"											//������� ��������� �������� � ��������� ������� �������� � ������� IN. ������� vec3(������� ����� ���������� ����������) � ��������� POSITION. ������� ����� ���������� ������� ����� layout (location = 0)
"layout (location = 1) in vec3 color;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0);\n"												//�.�. ��� ������� ������ ���������� �� ������ ������������� ��� � ������������� --->  �������� ���������� vec3 � vec4, � ���������� w ������ �������� 1.0f. (VEC4 ������ 4 FLOAT ����.)(��� BVEC, IVEC - ������� ������ bool ��� int)
"ourColor = color;\n"
"}\0";
//�������� ��� ������������ ������� (������������ ��� ��������� ������)
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"																	//��������� �������� ���������� � ������� ��������� ����� out, �� ��������  color. ����������� ������ ������� ������ �������� �����, ���������� 4 ������������ ��������.
"uniform vec4 ourColor;\n"															//�������� ���������� ����� ourColor ���� ������� �� 4 ��������� � ����������� ������� � ���������� �� ��� ��������� ��������� �������� ������������ �������								
"void main()\n"
"{\n"
"color = ourColor;\n"
"}\n\0";

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

	//�������� Opengl ������ ����
	int width;
	int height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);												//glViewport(<������� ������� ������ ���� ������1>, <������� ������� ������ ���� ������2>, <������>, <������>);
	//��������, ��� ��������������.
	if (glewInit() != GLEW_OK)
	{
		return 1;
	}
	glewInit();																		//�������������� ����� �������� �������� ��������� glfwMakeContextCurrent 

	glfwSetKeyCallback(window, key_callback);										//�������� ���-� �-�� � GLWF

	//��������� ������
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);							//1)������� ������ �������. GL_VERTEX_SHADER - ��� ������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);						//����������� ��� �������. 1�� �������� ��������� ������, ������� ��������� �������, 2��  ��������� ���������� �����(���� ������), 3�� - ��� ��� �������� ��� �������, 4�� �� ������� � NULL.
	glCompileShader(vertexShader);													//�������� ������
	//�������� �� �������� ���������� �������
	GLint success;																	//����� ��� ����������� ���������� ������
	GLchar infoLog[512];															//��������� ��� �������� ������
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);						//��������� ���������� � �������
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);						//���� ������ ���������� � ������� ��������� �� ������ � ������� glGetShaderInfoLog � ��������� ��� ������
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//����������� ������(���������� ����������)
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);						//2)������� ������ �������. GL_VERTEX_SHADER - ��� �������						
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);					//����������� ��� �������.
	glCompileShader(fragmentShader);												//�������� ������
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);						//��������
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//��� ����, ����� ������������ ��������� ������� �� ��������� ��������� � ������ ��������� ���������, � ����� ������������ ��� ��������� ��� ��������� ��������, � ��� ��������� ����� �������������� ��� ������ ������ ���������.
	GLuint shaderProgram = glCreateProgram();										//glCreateProgram ������� ��������� � ���������� ������������� ���� ���������										
	glAttachShader(shaderProgram, vertexShader);									//������� ��������� ������
	glAttachShader(shaderProgram, fragmentShader);									//������� ����������� ������
	glLinkProgram(shaderProgram);													//���������� � ���������
	//�������� ������ ��������
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) 
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}

	GLfloat vertices[] = 
	{
		 0.5f,  0.5f, 0.0f,  // Top Right
		 0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};
	GLuint indices[] = 
	{  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};

	//�������� EBO, VAO, EBO
	GLuint  VBO, VAO, EBO;
	glGenBuffers(1, &VBO);															//3)������� VBO ����� ��� �������
	glGenVertexArrays(1, &VAO);														//3)������� VAO ����� ��� �������(������ ��� �������������)	->����� ��������� ��������� VBO � ��������� �� ��������, � � ����� �������� VAO ��� ������������ �������������. ������ ��� ����� �� ����� ���������� ������ �� ������ ����������� VAO � ���������� ��� ����������� ����� ���������� �������
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);															//������ VAO (-> ���������� �������� VBO � ��������� �� �������� � VAO)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);												//4)�������� ���� ������� � ����� ��� OpenGL(������ ����� GL_ARRAY_BUFFER. ������ ����� �����, ������������ �����, ����� �������� � VBO. )
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		//4)�������� ���� ������� � ����� ��� OpenGL.����� glBufferData ��� ����������� ��������� ������ � ���� �����(����������� ������ ������������ � ��������� �����).1�������� �  ��� ������ � ������� �� ����� ����������� ������ (��� VBO ������ �������� � GL_ARRAY_BUFFER). 2�������� ���������� ���������� ������ (� ������), ������� ����� �������� ������. 3 �������� � ���  ������. 4�������� ���������� ��� �� ����� ����� ���������� �������� � ����������� �� �������(3 ������:GL_STATIC_DRAW: ������ ���� ������� �� ����� ����������(������ � ������� ������������ �������� �� �����), ���� ����� ���������� ����� �����; GL_DYNAMIC_DRAW: ������ ����� �������� �������� �����;GL_STREAM_DRAW: ������ ����� �������� ��� ������ ���������) (������ ��� ����������)). 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);//5)������������� ��������� �� ��������� ��������. 1-�� �������� - ����� �������� ������� ����� ���������(position - layout (location = 0)), 2�� �������� -  ������ ���������(�.�. vec3), 3��  ������������ ��� ������, 4�� ��������� ������������� ������������� ������� ������(���� ������ GL_TRUE, �� ��� ������ ����� ����������� ����� 0 (-1 ��� �������� ��������) � 1. ������������ �� ��������� -> ��������� GL_FALSE), 5�� ���(��������� ���������� ����� �������� ������), 6�� - ����� ��� GLvoid*-> ���������� ���������� �����. - ��� �������� ������ ������ � ������(� ��� ����� �� ����� �������� � �������  ��������� 0)
	glEnableVertexAttribArray(0);													//5)�.� ������� ������ �������� -> ��������
	glBindVertexArray(0);															//���������� Vao (����� ����� ����� ��������� "glBindVertexArray(VAO);" � ����� ����� ��������) 												
	

	while (!glfwWindowShouldClose(window))											//���������, �� �������� �� �������� ��������� ������ 
	{
		glfwPollEvents();															//��������� ������� � �������� ������� ��������� ������(����� ����� � ���������� ��� ����������� ����) � �������� ������������� �������
		
	//������� ��������� ...
		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);										//���� ����
		glClear(GL_COLOR_BUFFER_BIT);												//GlClear(<����� ���� ��������>) - �������� ����� (GL_COLOR_BUFFER_BIT - ��������,  GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT )��� ������ �� �������� glClear ���� ����� ����� �������� ��������� 	������.glClearColor � ��� ������� ��������������� ���������, � glClear � ��� ������� ������������ ���������.
		
		
		
		
		GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);								// 1�� ��. - � ��� �� ����� ������������ �������� � ������ ����� ���� �������������, � 2��-  ��� �� ����� ������������ ������ �����. ��� ����, ����� ��������� � ��������� ������������  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL).
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);											//��������� �������� �������� GL_TRIANGLES. 2�� �������� - ��� ������ �������  ������, 3�� ���������� ������
		glBindVertexArray(0);														//���������� VAO
	//�����.

		glfwSwapBuffers(window);													//�������� �������� �����, ������� ������������� ��� ��������� �� ����� ������� �������� � ���������� ��������� �� ������.
	}

	glfwTerminate();																//*�������� ���������� ��������
	glDeleteShader(vertexShader);													//�������� ��������� ��������
	glDeleteShader(fragmentShader);													//�������� ������������ �������
	glBindVertexArray(0);															//���������� VAO 

	return 0;
}
