#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glew.h>
#include <glfw3.h>
#include <SOIL.h>

#include "Model.h"
#include "Lamp.h"
#include "Jalousie.h"
#include "ReadFile.h"

using namespace glm;

extern Intilization intilizaton;

class MyHouse
{
public:
	GLuint  VBO, objectVAO, EBO;
	GLuint lightVAO;
	GLuint diffuseMap;
	unsigned int skyboxVAO, skyboxVBO;

	void init_cube_room()
	{
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
		glBindVertexArray(0);																					//���������� Vao (����� ����� ����� ��������� "glBindVertexArray(VAO);" � ����� ����� �������
	}

	void init_skybox()
	{
		float skyboxVertices[] = 
		{
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	}
	void init_cube_light()
	{
		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(lightVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}

	void init_texture(Shader ObjectShader, const char* path)
	{
		glBindVertexArray(0);
		glGenTextures(1, &diffuseMap);																	//6)�������� �������� (1�� ��� - ����������� �������, 2�� - ������ ��������������� �������)
		glBindTexture(GL_TEXTURE_2D, diffuseMap);															//������
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);									//1�� ��� - � ���� �������� ��������(2� - GL_TEXTURE_2D), 2�� ��� - ����� ��������(WRAP)(WRAP_S - ��� ��� S), 3�� - ����� wrapping(GL_MIRRORED_REPEAT)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);									//WRAP_T - ��� ��� T
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int width, height;
		unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);		//1�� - ���������� ����(GL_TEXTURE_2D), 2�� - ��������� ������� ������� ��� �������� �� ����� ������������� ��������(0 - ��������� �� OPENGL),	3�� - ����� ������� ������� ��������, 4�� - ������, 5�� - ������, 6�� - ����������(����� 0), 7�� - ������ �������(RGB), 8�� - ��� ������ �����������(�.�. ��������� ����������� � ������� � ������ (cha)r - GL_UNSIGNED_BYTE), 9�� - �����������
		glGenerateMipmap(GL_TEXTURE_2D);																//��������� ��������
		SOIL_free_image_data(image);																	//�������� ��.������ ��� �������	
		glBindTexture(GL_TEXTURE_2D, 1);
		ObjectShader.Use();
		glUniform1i(glGetUniformLocation(ObjectShader.Program, "material.diffuse"), 0);
	}

	void Draw(Utils utils, Shader ObjectShader, Shader LampShader, GLFWwindow* window, Shader skybox)
	{
		Lamp lamp;
		Jalousie jalousie;
		ReadFile txt;

		vec3 pointLightPositions[] =
		{
			vec3(0.0f,  0.8f,  -0.8f),
			vec3(-0.5f, 0.8f, -0.8f),
			vec3(-1.0f,  0.8f, -0.8f),

			vec3(0.0f, 0.5f, 4.0f),
			vec3(0.0f, 0.5f, 4.4f),
			vec3(0.0f, 0.5f, 4.8f),

			vec3(3.07f, 0.5f, 0.0f),
			vec3(3.15f, 0.5f, 0.0f),
			vec3(3.2f, 0.5f, 0.0f),

			vec3(3.07f, 0.8f, -3.7f),
			vec3(3.15f, 0.8f, -3.7f),
			vec3(3.2f, 0.8f, -3.7f),

			vec3(0.0f, 5.0f, -13.0f)
		};

		vector<string> faces
		{
			"../skybox/right.jpg",
			"../skybox/left.jpg",
			"../skybox/top.jpg",
			"../skybox/bottom.jpg",
			"../skybox/front.jpg",
			"../skybox/back.jpg",
		};

		unsigned int cubemapTexture = utils.loadCubemap(faces);
		LampShader.Use();
		LampShader.setInt("skybox", 0);
		glBindVertexArray(0);

		ObjectShader.Use();
		lamp.on_min_all_lamp(ObjectShader);
		lamp.init_all_lights(ObjectShader, pointLightPositions);

		Model Bed(const_cast<GLchar*>("../Models/Bed/Full_Size_Bed_with_White_Sheets_Black_V1.obj"));
		Model Door(const_cast<GLchar*>("../Models/Room-door/Door_Component_BI3.obj"));
		Model Window(const_cast<GLchar*>("../Models/Window/Window_Component_BI_Weight_Paint2.obj"));
		Model Grass(const_cast<GLchar*>("../Models/Grass/10450_Rectangular_Grass_Patch_v1_iterations-2.obj"));
		Model Refregarator(const_cast<GLchar*>("../Models/Refregerator/Refrigerator.obj"));
		Model Table_kitchen(const_cast<GLchar*>("../Models/Table_kitchen/Kitchen furniture.obj"));
		Model Sofa(const_cast<GLchar*>("../Models/Sofa/DesignSofa1.obj"));
		Model Toilet(const_cast<GLchar*>("../Models/Toilet/10778_Toilet_V2.obj"));
		Model OUTair(const_cast<GLchar*>("../Models/OUTair/10780_AirConditioner_V4_LOD3.obj"));
		Model Fence(const_cast<GLchar*>("../Models/Fence/13076_Gothic_Wood_Fence_Panel_v2_l3.obj"));
		Model INair(const_cast<GLchar*>("../Models/INair/zabyl.obj"));
		Model Humidifier(const_cast<GLchar*>("../Models/Humidifier/humidifier.obj"));

		while (!glfwWindowShouldClose(window))											//���������, �� �������� �� �������� ��������� ������ 
		{
			GLfloat currentFrame = glfwGetTime();
			intilizaton.SetDeltaTime(currentFrame - intilizaton.GetLastFrame());
			intilizaton.SetLastFrame(currentFrame);

			glfwPollEvents();															//��������� ������� � �������� ������� ��������� ������(����� ����� � ���������� ��� ����������� ����) � �������� ������������� �������
			utils.movement(intilizaton);

			glClearColor(0.5f, 0.3f, 1.0f, 1.0f);										//���� ����
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);							//GlClear(<����� ���� ��������>) - �������� ����� (GL_COLOR_BUFFER_BIT - ��������,  GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT )��� ������ �� �������� glClear ���� ����� ����� �������� ��������� 	������.glClearColor � ��� ������� ��������������� ���������, � glClear � ��� ������� ������������ ���������

		//������� ��������� ...

			ObjectShader.Use();

			ObjectShader.setVec3("viewPos", camera.GetPosition());
			ObjectShader.setFloat("material.shininess", 64.0f);
			
			ObjectShader.setVec3("dirLight.direction", 0.0f, 5.0f, -13.0f);
			ObjectShader.setVec3("dirLight.ambient", 0.005f, 0.005f, 0.005f);
			ObjectShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
			ObjectShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
			/*
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
			mat4 projection = perspective(90.0f, (float)intilizaton.GetWidht() / (float)intilizaton.GetWidht(), 0.1f, 100.0f);				//������� ��������, ������������ ���� ������: 45.0f - ���� ������ = fov
			mat4 view = camera.GetViewMatrix();																								//������� ���� LookAt, ������������ �� ������� ������, ���������� ���� � ������� ������������� �����
			ObjectShader.setMat4("projection", projection);
			ObjectShader.setMat4("view", view);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuseMap);
			glBindVertexArray(objectVAO);
			mat4 model = mat4(1.0f);
			model = scale(model, vec3(4.0f, 2.0f, 8.0f));
			ObjectShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = mat4(1.0f);
			model = scale(model, vec3(4.0f, 2.0f, 2.5f));
			model = translate(model, vec3(0.0f, 0.0f, 2.093f));
			ObjectShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = mat4(1.0f);
			model = scale(model, vec3(2.0f));
			model = translate(model, vec3(1.501f, 0.0f, 0.0f));
			ObjectShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			
			model = mat4(1.0f);
			model = scale(model, vec3(2.5f, 2.0f, 2.5f));
			model = translate(model, vec3(1.301f, 0.0f, -1.0f));
			ObjectShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			
			model = mat4(1.0f);
			model = scale(model, vec3(9.7f, 1.0f, 13.0f));
			model = translate(model, vec3(0.0f, -1.51f, 0.15f));
			model = rotate(model, 90.0f, vec3(0.0f, 0.0f, 1.0f));
			ObjectShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = mat4(1.0f);
			model = translate(model, vec3(0.4f, -0.5f, 5.0f));
			model = scale(model, vec3(0.01f));
			model = rotate(model, 270.0f, vec3(1.0f, 0.0f, 0.0f));
			ObjectShader.setMat4("model", model);
			Bed.Draw(ObjectShader);

			model = mat4(1.0f);
			model = translate(model, vec3(2.35f, -0.35f, -3.3f));
			model = scale(model, vec3(0.9f, 0.9f, 0.9f));
			model = rotate(model, 270.0f, vec3(0.0f, 1.0f, 0.0f));
			ObjectShader.setMat4("model", model);
			Refregarator.Draw(ObjectShader);

			model = mat4(1.0f);
			model = translate(model, vec3(4.15f, -1.0f, -2.1f));
			model = scale(model, vec3(0.009f));
			model = rotate(model, 180.0f, vec3(0.0f, 1.0f, 0.0f));
			ObjectShader.setMat4("model", model);
			Table_kitchen.Draw(ObjectShader);

			model = mat4(1.0f);
			model = translate(model, vec3(0.0f, -1.0f, -3.38f));
			model = scale(model, vec3(0.4f));
			ObjectShader.setMat4("model", model);
			Sofa.Draw(ObjectShader);

			model = mat4(1.0f);
			model = translate(model, vec3(3.0f, -0.5f, 0.0f));
			model = scale(model, vec3(0.02f));
			model = rotate(model, 270.0f, vec3(1.0f, 0.0f, 0.0f));
			ObjectShader.setMat4("model", model);
			Toilet.Draw(ObjectShader);
			
			model = mat4(1.0f);
			model = translate(model, vec3(-0.85f, -1.0f, 4.06f));
			model = scale(model, vec3(0.8f));
			model = rotate(model, 180.0f, vec3(0.0f, 1.0f, 0.0f));
			ObjectShader.setMat4("model", model);
			Door.Draw(ObjectShader);
			
			model = mat4(1.0f);
			model = translate(model, vec3(2.07f, -1.0f, 0.0f));
			model = scale(model, vec3(0.8f));
			model = rotate(model, 270.0f, vec3(0.0f, 1.0f, 0.0f));
			ObjectShader.setMat4("model", model);
			Door.Draw(ObjectShader);

			model = mat4(1.0f);
			model = translate(model, vec3(2.07f, -1.0f, -1.7f));
			model = scale(model, vec3(0.8f));
			model = rotate(model, 270.0f, vec3(0.0f, 1.0f, 0.0f));
			ObjectShader.setMat4("model", model);
			Door.Draw(ObjectShader);

			model = mat4(1.0f);
			model = translate(model, vec3(-1.94f, -1.0f, 0.0f));
			model = scale(model, vec3(0.8f));
			model = rotate(model, 270.0f, vec3(0.0f, 1.0f, 0.0f));
			ObjectShader.setMat4("model", model);
			Door.Draw(ObjectShader);
			
			model = mat4(1.0f);
			model = translate(model, vec3(0.0f, -0.5f, -3.95f));
			model = scale(model, vec3(0.5f));
			ObjectShader.setMat4("model", model);
			Window.Draw(ObjectShader);

			model = mat4(1.0f);
			model = translate(model, vec3(3.98f, -0.5f, 0.0f));
			model = scale(model, vec3(0.5f));
			model = rotate(model, 270.0f, vec3(0.0f, 1.0f, 0.0f));
			ObjectShader.setMat4("model", model);
			Window.Draw(ObjectShader);
			
			model = mat4(1.0f);
			model = translate(model, vec3(3.07f, -0.5f, -3.7f));
			model = scale(model, vec3(0.5f));
			ObjectShader.setMat4("model", model);
			Window.Draw(ObjectShader);
			
			model = mat4(1.0f);
			model = translate(model, vec3(0.0f, -0.5f, 6.52f));
			model = scale(model, vec3(0.5f));
			ObjectShader.setMat4("model", model);
			Window.Draw(ObjectShader);

			model = mat4(1.0f);
			model = translate(model, vec3(0.0f, -0.5f, 6.52f));
			model = scale(model, vec3(0.5f));
			ObjectShader.setMat4("model", model);
			Window.Draw(ObjectShader);

			//txt.read_txt(ObjectShader, lamp, jalousie);
		
			txt.read_txt2(ObjectShader, lamp, jalousie);
			


			
			glBindVertexArray(objectVAO);
			switch (true)
			{
			case 1:
			{
				switch (jalousie.GetMode(1))
				{
				case 0:
				{
					for (float i = 0.0f; i < 7.0f; i++)
					{
						model = mat4(1.0f);
						model = translate(model, vec3((-0.3 + i / 10), 0.0f, -3.8f));
						model = scale(model, vec3(0.08f, 1.4f, 0.01f));
						ObjectShader.setMat4("model", model);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}

					break;
				}
				case 90:
				{
					for (float i = 0.0f; i < 7.0f; i++)
					{
						model = mat4(1.0f);
						model = translate(model, vec3((-0.3 + i / 10), 0.0f, -3.8f));
						model = scale(model, vec3(0.01f, 1.4f, 0.08f));
						ObjectShader.setMat4("model", model);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}

					break;
				}
				
				case 60:
				{
					for (float i = 0.0f; i < 7.0f; i++)
					{
						model = mat4(1.0f);
						model = translate(model, vec3((-0.3 + i / 10), 0.0f, -3.8f));
						model = rotate(model, 45.0f, vec3(0.0f, 1.0f, 0.0f));
						model = scale(model, vec3(0.1f, 1.4f, 0.015f));
						ObjectShader.setMat4("model", model);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}

					break;
				}
				}
			}
			case 2:
			{
				switch (jalousie.GetMode(2))
				{
				case 0:
				{
					for (float i = 0.0f; i < 7.0f; i++)
					{
						model = mat4(1.0f);
						model = translate(model, vec3((-0.25f + i / 10), 0.0f, 6.42f));
						model = scale(model, vec3(0.08f, 1.4f, 0.01f));
						ObjectShader.setMat4("model", model);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}

					break;
				}
				case 90:
				{
					for (float i = 0.0f; i < 7.0f; i++)
					{
						model = mat4(1.0f);
						model = translate(model, vec3((-0.25f + i / 10), 0.0f, 6.42f));
						model = scale(model, vec3(0.01f, 1.4f, 0.08f));
						ObjectShader.setMat4("model", model);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}

					break;
				}
				case 60:
				{
					for (float i = 0.0f; i < 7.0f; i++)
					{
						model = mat4(1.0f);
						model = translate(model, vec3((-0.25f + i / 10), 0.0f, 6.42f));
						model = rotate(model, 45.0f, vec3(0.0f, 1.0f, 0.0f));
						model = scale(model, vec3(0.1f, 1.4f, 0.015f));
						ObjectShader.setMat4("model", model);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}

					break;
				}
				}
			}
			case 3:
			{
				switch (jalousie.GetMode(3))
				{
				case 0:
				{
					for (float i = 0.0f; i < 7.0f; i++)
					{
						model = mat4(1.0f);
						model = translate(model, vec3((2.8f + i/10), 0.0f, -3.6f));
						model = scale(model, vec3(0.08f, 1.4f, 0.01f));
						ObjectShader.setMat4("model", model);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}

					break;
				}
				case 90:
				{
					for (float i = 0.0f; i < 7.0f; i++)
					{
						model = mat4(1.0f);
						model = translate(model, vec3((2.8f + i / 10), 0.0f, -3.6f));
						model = scale(model, vec3(0.01f, 1.4f, 0.08f));
						ObjectShader.setMat4("model", model);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}

					break;
				}
				case 60:
				{
					for (float i = 0.0f; i < 7.0f; i++)
					{
						model = mat4(1.0f);
						model = translate(model, vec3((2.8f + i / 10), 0.0f, -3.6f));
						model = rotate(model, 45.0f, vec3(0.0f, 1.0f, 0.0f));
						model = scale(model, vec3(0.1f, 1.4f, 0.015f));
						ObjectShader.setMat4("model", model);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}

					break;
				}
				}
			}
			case 4:
			{
				switch (jalousie.GetMode(4))
				{
				case 0:
				{
					for (float i = 0.0f; i < 7.0f; i++)
					{
						model = mat4(1.0f);
						model = translate(model, vec3(3.86f, 0.0f, (-0.2f + i / 10)));
						model = scale(model, vec3(0.01f, 1.4f, 0.08f));
						ObjectShader.setMat4("model", model);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}

					break;
				}
				case 90:
				{
					for (float i = 0.0f; i < 7.0f; i++)
					{
						model = mat4(1.0f);
						model = translate(model, vec3(3.86f, 0.0f, (-0.2f + i / 10)));
						model = scale(model, vec3(0.08f, 1.4f, 0.01f));
						ObjectShader.setMat4("model", model);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}

					break;
				}
				case 60:
				{
					for (float i = 0.0f; i < 7.0f; i++)
					{
						model = mat4(1.0f);
						model = translate(model, vec3(3.86f, 0.0f, (-0.2f + i / 10)));
						model = rotate(model, 45.0f, vec3(0.0f, 1.0f, 0.0f));
						model = scale(model, vec3(0.1f, 1.4f, 0.015f));
						ObjectShader.setMat4("model", model);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}

					break;
				}
				}
				break;
			}
			}		

			lamp.change_brightness_depended_jalousie(ObjectShader, jalousie.Get_count_closer_jalousie());

			for (int i = 0; i < 4; i++)
			{
				cout << jalousie.mode_j[i] << "  ";
			}
			cout << endl;

			model = mat4(1.0f);
			model = translate(model, vec3(0.0f));
			model = scale(model, vec3(0.05f));
			ObjectShader.setMat4("model", model);
			Humidifier.Draw(ObjectShader);

			model = mat4(1.0f);
			model = translate(model, vec3(0.0f, -2.21f, 0.0f));
			model = scale(model, vec3(0.1f));
			model = rotate(model, 270.0f, vec3(1.0f, 0.0f, 0.0f));
			ObjectShader.setMat4("model", model);
			Grass.Draw(ObjectShader);

			for (int i = 0; i < 3; i++)
			{
				model = mat4(1.0f);
				model = translate(model, vec3((3.0f - 3 * i), -1.0f, -4.5f));
				model = scale(model, vec3(0.018, 0.005f, 0.018f));
				model = rotate(model, 270.0f, vec3(1.0f, 0.0f, 0.0f));
				ObjectShader.setMat4("model", model);
				Fence.Draw(ObjectShader);

				model = mat4(1.0f);
				model = translate(model, vec3((2.9f - 3 * i), -1.0f, 8.5f));
				model = scale(model, vec3(0.018, 0.005f, 0.018f));
				model = rotate(model, 270.0f, vec3(1.0f, 0.0f, 0.0f));
				ObjectShader.setMat4("model", model);
				Fence.Draw(ObjectShader);
			}
			for (int i = 0; i < 4; i++)
			{
				model = mat4(1.0f);
				model = translate(model, vec3(-4.7f, -1.0f, (-2.7 + 3 * i)));
				model = scale(model, vec3(0.018, 0.005f, 0.018f));
				model = rotate(model, 270.0f, vec3(1.0f, 0.0f, 0.0f));
				model = rotate(model, 90.0f, vec3(0.0f, 0.0f, 1.0f));
				ObjectShader.setMat4("model", model);
				Fence.Draw(ObjectShader);

				model = mat4(1.0f);
				model = translate(model, vec3(5.0f, -1.0f, (-2.7 + 3 * i)));
				model = scale(model, vec3(0.02, 0.005f, 0.02f));
				model = rotate(model, 270.0f, vec3(1.0f, 0.0f, 0.0f));
				model = rotate(model, 90.0f, vec3(0.0f, 0.0f, 1.0f));
				ObjectShader.setMat4("model", model);
				Fence.Draw(ObjectShader);
			}

			model = mat4(1.0f);
			model = translate(model, vec3(-2.4f, 0.0f, -2.0f));
			model = scale(model, vec3(0.03f, 0.03f, 0.03f));
			model = rotate(model, 270.0f, vec3(1.0f, 0.0f, 0.0f));
			model = rotate(model, 270.0f, vec3(0.0f, 0.0f, 1.0f));
			ObjectShader.setMat4("model", model);
			OUTair.Draw(ObjectShader);

			model = mat4(1.0f);
			model = translate(model, vec3(-1.9f, 0.7f, -2.0f));
			model = scale(model, vec3(0.08f, 0.15f, 0.15f));
			model = rotate(model, 90.0f, vec3(0.0f, 1.0f, 0.0f));
			ObjectShader.setMat4("model", model);
			INair.Draw(ObjectShader);

			glBindVertexArray(0);
			
			LampShader.Use();
			glBindVertexArray(lightVAO);
			LampShader.setMat4("projection", projection);
			LampShader.setMat4("view", view);
			for (size_t i = 0; i < 13; i++)
			{
				model = mat4(1.0f);
				model = translate(model, pointLightPositions[i]);
				model = scale(model, glm::vec3(0.025f));
				LampShader.setMat4("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			glBindVertexArray(lightVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
			glDepthFunc(GL_LEQUAL);
			skybox.Use();
			view = mat4(mat3(camera.GetViewMatrix()));
			skybox.setMat4("view", view);
			skybox.setMat4("projection", projection);
			// skybox cube
			glBindVertexArray(skyboxVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
			glDepthFunc(GL_LESS);
			
			glfwSwapBuffers(window);												//�������� �������� �����, ������� ������������� ��� ��������� �� ����� ������� �������� � ���������� ��������� �� ������.
		}
		glfwTerminate();															//*�������� ���������� ��������
	}

	~MyHouse()
	{
		glDeleteVertexArrays(1, &objectVAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteVertexArrays(1, &skyboxVAO);
		glDeleteBuffers(1, &skyboxVAO);
	}

private:
};