#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glew.h>
#include <glfw3.h>
#include <SOIL.h>

#include "Model.h"
#include "Lamp.h"

glm::vec3 pointLightPositions[] =
{
	glm::vec3(0.0f,  0.0f,  -0.5f),
	glm::vec3(0.5f, 0.0f, -0.5f),
	glm::vec3(-0.5f,  0.0f, -0.5f),
	glm::vec3(-4.0f,  5.0f, -5.0f),
};

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
	GLuint diffuseMap;																	

	void create_cube_room()
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
	}

	void create_cube_light()
	{
		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(lightVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}

	void crete_texture_cube_room(Shader ObjectShader)
	{
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
		ObjectShader.Use();
		glUniform1i(glGetUniformLocation(ObjectShader.Program, "material.diffuse"), 0);
	}

	void Draw(Utils utils, Shader ObjectShader, Shader LampShader, GLFWwindow* window)
	{
		Lamp lamp;

		ObjectShader.Use();

		lamp.on_max_all_lamp(ObjectShader);
		lamp.init_all_lamp(ObjectShader, pointLightPositions);
		ObjectShader.setBool("off", false);
	

		Model Bed(const_cast<GLchar*>("../Models/bed/Full_Size_Bed_with_White_Sheets_Black_V1.obj"));
		Model Door(const_cast<GLchar*>("../Models/Room-door/Door_Component_BI3.obj"));
		Model Room(const_cast<GLchar*>("../Models/window/Window_Component_BI_Weight_Paint2.obj"));

		while (!glfwWindowShouldClose(window))											//���������, �� �������� �� �������� ��������� ������ 
		{
			GLfloat currentFrame = glfwGetTime();
			intilizaton.deltaTime = currentFrame - intilizaton.lastFrame;
			intilizaton.lastFrame = currentFrame;

			glfwPollEvents();															//��������� ������� � �������� ������� ��������� ������(����� ����� � ���������� ��� ����������� ����) � �������� ������������� �������
			utils.movement();

			glClearColor(0.5f, 0.3f, 1.0f, 1.0f);										//���� ����
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);							//GlClear(<����� ���� ��������>) - �������� ����� (GL_COLOR_BUFFER_BIT - ��������,  GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT )��� ������ �� �������� glClear ���� ����� ����� �������� ��������� 	������.glClearColor � ��� ������� ��������������� ���������, � glClear � ��� ������� ������������ ���������

		//������� ��������� ...
			
			ObjectShader.Use();
			lamp.brightness(ObjectShader);

			ObjectShader.setVec3("viewPos", camera.Position);
			ObjectShader.setFloat("material.shininess", 32.0f);
			/*
			ObjectShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
			ObjectShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
			ObjectShader.setVec3("dirLight.diffuse", 0.8f, 0.8f, 0.8f);
			ObjectShader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);
			ObjectShader.setVec3("spotLight.position", camera.Position);
			ObjectShader.setVec3("spotLight.direction", camera.Front);
			ObjectShader.setVec3("spotLight.ambient", 0.05f, 0.05f, 0.05f);
			ObjectShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
			ObjectShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
			ObjectShader.setFloat("spotLight.constant", 1.0f);
			ObjectShader.setFloat("spotLight.linear", 0.09);
			ObjectShader.setFloat("spotLight.quadratic", 0.032);
			ObjectShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
			ObjectShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
			*/

			glm::mat4 projection = glm::perspective(45.0f, (float)intilizaton.GetWidht() / (float)intilizaton.GetWidht(), 0.1f, 100.0f);
			glm::mat4 view = camera.GetViewMatrix();
			ObjectShader.setMat4("projection", projection);
			ObjectShader.setMat4("view", view);

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::scale(model, glm::vec3(3.0f, 2.0f, 4.0f));
			ObjectShader.setMat4("model", model);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuseMap);
			glBindVertexArray(objectVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);

			model = glm::mat4(1.0f);
			model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
			model = glm::translate(model, glm::vec3(0.3f, 0.0225f, 1.0f));
			ObjectShader.setMat4("model", model);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuseMap);
			glBindVertexArray(objectVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			ObjectShader.Use();
			ObjectShader.setMat4("projection", projection);
			ObjectShader.setMat4("view", view);
			glBindVertexArray(lightVAO);
			for (unsigned int i = 0; i < 4; i++)
			{
				model = glm::mat4(1.0f);
				model = glm::translate(model, pointLightPositions[i]);
				model = glm::scale(model, glm::vec3(0.2f)); 
				ObjectShader.setMat4("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			model = glm::mat4(1.0f);
			model = glm::scale(model, glm::vec3(1.2, 1.3, 1.2));
			//model = glm::rotate(model, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(1.0f, -0.8f, 1.47f));
			ObjectShader.setMat4("model", model);
			Door.Draw(ObjectShader);
			
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(1.0f, -1.7f, 6.0f));
			model = glm::rotate(model, 90.0f, glm::vec3(0.0f, 1.0f, 1.0f));
			model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
			ObjectShader.setMat4("model", model);
			Bed.Draw(ObjectShader);

			
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, -0.75f, -3.97f));
			//model = glm::rotate(model, 90.0f, glm::vec3(0.0f, 1.0f, 1.0f));
			model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
			ObjectShader.setMat4("model", model);
			Room.Draw(ObjectShader);


			/*
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, -7.8f, 0.0f));
			model = glm::rotate(model, 90.0f, glm::vec3(0.0f, 1.0f, 1.0f));
			model = glm::scale(model, glm::vec3(1.1, 1.1, 1.1));
			ObjectShader.setMat4("model", model);
			Grass.Draw(ObjectShader);
			

			

			
			LampShader.Use();
			LampShader.setMat4("projection", projection);
			LampShader.setMat4("view", view);
			model = glm::mat4(1.0f);
			model = glm::translate(model, intilizaton.GetlightPos());
			model = glm::rotate(model, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(2.0, 0.1, 0.1));
			LampShader.setMat4("model", model);
			glBindVertexArray(lightVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
			//�����.
			
			*/
			glfwSwapBuffers(window);												//�������� �������� �����, ������� ������������� ��� ��������� �� ����� ������� �������� � ���������� ��������� �� ������.
		}
		glfwTerminate();															//*�������� ���������� ��������
	}

	~MyRoom()
	{
		glDeleteVertexArrays(1, &objectVAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	
private:
};