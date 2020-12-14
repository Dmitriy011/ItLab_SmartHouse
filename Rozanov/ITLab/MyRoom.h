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
	0, 1, 3,																	// 1ый треугольник
	1, 2, 3																		// 2ой треугольник
};

class MyRoom
{
public:
	GLuint  VBO, objectVAO, EBO;
	GLuint lightVAO;
	GLuint diffuseMap;																				//6)Создание текстур	

	void create_RoomAndLight()
	{
		
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
		glBindVertexArray(0);																					//Отвязываем Vao (далее можно снова привязать "glBindVertexArray(VAO);" и необх снова отвязать)
	
		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(lightVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);																			
		// Texture 1
		glGenTextures(1, &diffuseMap);																	//6)Создание текстуры (1ый арг - колличество текстур, 2ой - массив идентификаторов текстур)
		glBindTexture(GL_TEXTURE_2D, diffuseMap);															//Привяз
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);									//1ый арг - к чему привязаа текстура(2д - GL_TEXTURE_2D), 2ой арг - опция текстуры(WRAP)(WRAP_S - для оси S), 3ий - метод wrapping(GL_MIRRORED_REPEAT)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);									//WRAP_T - для оси T
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int width, height;
		unsigned char* image = SOIL_load_image("../Pics/floor.jpg", &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);		//1ый - текстурная цель(GL_TEXTURE_2D), 2ой - описывает уровень мипмапа для которого мы хотим сгенерировать текстуру(0 - генерация на OPENGL),	3ий - каком формате хранить текстуру, 4ый - ширина, 5ый - высота, 6ой - утсаревший(всегд 0), 7ой - формат изображ(RGB), 8ой - тип данных изображения(т.к. загружали изображение и хранили в байтах (cha)r - GL_UNSIGNED_BYTE), 9ый - изображение
		glGenerateMipmap(GL_TEXTURE_2D);																//Генерация мипмапов
		SOIL_free_image_data(image);																	//Освобожд уч.памяти под изображ	
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