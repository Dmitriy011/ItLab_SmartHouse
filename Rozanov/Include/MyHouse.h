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
			0, 1, 3,																	// 1ый треугольник
			1, 2, 3																		// 2ой треугольник
		};

		glGenBuffers(1, &VBO);															//Создаем VBO через эту функцию,											
		glGenVertexArrays(1, &objectVAO);														//VAO
		glGenBuffers(1, &EBO);															//EBO
		glBindVertexArray(objectVAO);															//Привяз VAO(-> необходимо привзять VBO и указатели на атрибуты к VAO)
		glBindBuffer(GL_ARRAY_BUFFER, VBO);												//4)Все данные, которые хотим хранить VBO будут в буфере GL_ARRAY_BUFFER(привяз буфер GL_ARRAY_BUFFER. Теперь любой вызов, использующий буфер, будет работать с VBO.) (GL_ELEMENT_ARRAY_BUFFER используется для обозначения буфера, который)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);										//4)(GL_ELEMENT_ARRAY_BUFFER используется для обозначения буфера, который содержит индексы каждого элемента в буфере GL_ARRAY_BUFFER)
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		//4)Копируем наши вершины в буфер для OpenGL.Вызов glBufferData для копирования вершинных данных в этот буфер(копирование данных пользователя в указанный буфер).1аргумент —  тип буфера в который мы хотим скопировать данные (наш VBO сейчас привязан к GL_ARRAY_BUFFER). 2ой - определяет количество данных (в байтах), которые хотим передать буферу. 3 аргумент — это  данные. 4аргумент определяет как мы хотим чтобы видеокарта работала с переданными ей данными(3 режима:GL_STATIC_DRAW: данные либо никогда не будут изменяться(Данные о позиции треугольника меняться не будут), либо будут изменяться очень редко; GL_DYNAMIC_DRAW: данные будут меняться довольно часто;GL_STREAM_DRAW: данные будут меняться при каждой отрисовке) (Данные для видеокарты)). 
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//4)Копируем индексы вершин 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);						//5)Атрибут для вершин: Устанавливаем указатели на вершинные атрибуты. 1-ый аргумент - какой параметр шейдера хотим настриоть(position - layout (location = 0)), 2ой аргумент -  размер аргумента(т.к. vec3), 3ий  используемый тип данных, 4ый указывает необходимость нормализовать входные данные(Если укажем GL_TRUE, то все данные будут расположены между 0 (-1 для знаковых значений) и 1. Нормализация не требуется -> оставляем GL_FALSE), 5ый шаг(описывает расстояние между наборами данных), 6ой - имеет тип GLvoid*-> необходимо приведение типов. - ЭТО смещение начала данных в буфере(У нас буфер не имеет смещения и поэтому  указываем 0)
		glEnableVertexAttribArray(0);																			//5)Т.к атрибут вершин отключен -> включить
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));	//5)Атрибут цвета:
		glEnableVertexAttribArray(1);																			//5)Вкл
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));	//5)Атрибут расположения текстуры
		glEnableVertexAttribArray(2);																			//5)Вкл					
		glBindVertexArray(0);																					//Отвязываем Vao (далее можно снова привязать "glBindVertexArray(VAO);" и необх снова отвязат
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
		glGenTextures(1, &diffuseMap);																	//6)Создание текстуры (1ый арг - колличество текстур, 2ой - массив идентификаторов текстур)
		glBindTexture(GL_TEXTURE_2D, diffuseMap);															//Привяз
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);									//1ый арг - к чему привязаа текстура(2д - GL_TEXTURE_2D), 2ой арг - опция текстуры(WRAP)(WRAP_S - для оси S), 3ий - метод wrapping(GL_MIRRORED_REPEAT)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);									//WRAP_T - для оси T
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int width, height;
		unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);		//1ый - текстурная цель(GL_TEXTURE_2D), 2ой - описывает уровень мипмапа для которого мы хотим сгенерировать текстуру(0 - генерация на OPENGL),	3ий - каком формате хранить текстуру, 4ый - ширина, 5ый - высота, 6ой - утсаревший(всегд 0), 7ой - формат изображ(RGB), 8ой - тип данных изображения(т.к. загружали изображение и хранили в байтах (cha)r - GL_UNSIGNED_BYTE), 9ый - изображение
		glGenerateMipmap(GL_TEXTURE_2D);																//Генерация мипмапов
		SOIL_free_image_data(image);																	//Освобожд уч.памяти под изображ	
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

		while (!glfwWindowShouldClose(window))											//проверяет, не передано ли указание закончить работу 
		{
			GLfloat currentFrame = glfwGetTime();
			intilizaton.SetDeltaTime(currentFrame - intilizaton.GetLastFrame());
			intilizaton.SetLastFrame(currentFrame);

			glfwPollEvents();															//Проверяем события и вызываем функции обратного вызова(вроде ввода с клавиатуры или перемещение мыши) и вызывает установленные функции
			utils.movement(intilizaton);

			glClearColor(0.5f, 0.3f, 1.0f, 1.0f);										//Цвет окна
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);							//GlClear(<какие биты очистить>) - очистить буфер (GL_COLOR_BUFFER_BIT - цветовой,  GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT )Как только мы вызываем glClear весь буфер будет заполнен указанным 	цветом.glClearColor — это функция устанавливающая состояние, а glClear — это функция использующая состояние

		//Команды отрисовки ...

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
			mat4 projection = perspective(90.0f, (float)intilizaton.GetWidht() / (float)intilizaton.GetWidht(), 0.1f, 100.0f);				//матрица проекции, определяющая поле обзора: 45.0f - угол обзора = fov
			mat4 view = camera.GetViewMatrix();																								//матрица вида LookAt, составленная из позиции камеры, координаты цели и вектора направленнего вверх
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
			
			glfwSwapBuffers(window);												//заменяет цветовой буфер, который использовался для отрисовки во время текущей итерации и показывает результат на экране.
		}
		glfwTerminate();															//*очистить выделенные рессурсы
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