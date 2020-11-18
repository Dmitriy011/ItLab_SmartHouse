// GLEW нужно подключать до GLFW.
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

const GLuint WIDTH = 800, HEIGHT = 600;												//Размер окна

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

//----// Для разных комьютеров сокрость передвижения разная -> вычисл время затраченное на визуализацию и от него зависит скорость
GLfloat deltaTime = 0.0f;															// время, затраченное на визуализацию последнего выведенного кадра
GLfloat lastFrame = 0.0f;															// время вывода последнего кадра


int main(int argc, char** argv)														//argc число аргументов, argv массив аргументов
{

	//Инициализация GLFW. Настройка GLFW
	glfwInit();	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);									//glfwWindowHint(<идентификатор параметра, который подвергается изменению>, <значение, которое устанавливается соответствующему параметру>).GLFW_CONTEXT_VERSION_MAJOR и GLFW_CONTEXT_VERSION_MINOR указывают версию клиентского API(программного интерфейса приложения), с которым должен быть совместим созданный контекст
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);					//GLFW_OPENGL_PROFILE указывает, для какого профиля OpenGL создать контекст.(GLFW_OPENGL_CORE_PROFILE или GLFW_OPENGL_COMPAT_PROFILE или GLFW_OPENGL_ANY_PROFILE, чтобы не запрашивать конкретный профиль. Если запрашивается версия OpenGL ниже 3.2, необходимо использовать GLFW_OPENGL_ANY_PROFIL)
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);										//Выключение возможности изменения размера окна

	GLFWwindow* window = glfwCreateWindow(800, 600, "Room1", nullptr, nullptr);		//ширина, высота. Возвращает указатель на объект типа GLFWwindow
	if (window == nullptr)															//проверка на создание
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();															//Очистить рессурсы		
		return -1;
	}
	glfwMakeContextCurrent(window);													//Прежде чем мы сможем использовать команды для визуализации в созданное окно его нужно сделать его текущим контекстом

	glViewport(0, 0, WIDTH, HEIGHT);												//Сообщить Opengl размер окна - glViewport(<позиция нижнего левого угла экрана1>, <позиция нижнего левого угла экрана2>, <ширина>, <высота>);
	//проверка, что инцилизируется.
	if (glewInit() != GLEW_OK)
	{
		return 1;
	}
	glewInit();																		//Инцилизируется после создания текущего контекста glfwMakeContextCurrent 

	glEnable(GL_DEPTH_TEST);														//Вкл, чтобы OpenGL  выполнял проверку глубины, включая парамтер параметр GL_DEPTH_TEST	

	glfwSetKeyCallback(window, key_callback);										//Передаем сущ-ие ф-ии в GLWF

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);					//Захват курсора мыши для окна.

	glfwSetCursorPosCallback(window, mouse_callback);								//Передаем сущ-ие ф-ии в GLWF

	Shader ourShader("../Shader/Vertex/Vertex.txt", "../Shader/Fragment/fragment.txt ");

	float vertices[] = 
	{
	-4.5f, 0.0f, -2.75f,  0.0f, 0.0f,	//1тр
	 4.5f, 0.0f, -2.75f,  1.0f, 0.0f,
	 4.5f,  2.5f, -2.75f,  1.0f, 1.0f,
	 4.5f,  2.5f, -2.75f,  1.0f, 1.0f,	//2тр
	-4.5f,  2.5f, -2.75f,  0.0f, 1.0f,
	-4.5f, 0.0f, -2.75f,  0.0f, 0.0f,

	-4.5f, 0.0f,  2.75f,  0.0f, 0.0f,	//1тр
	 4.5f, 0.0f,  2.75f,  1.0f, 0.0f,
	 4.5f,  2.5f,  2.75f,  1.0f, 1.0f,
	 4.5f,  2.5f,  2.75f,  1.0f, 1.0f,	//2тр
	-4.5f,  2.5f,  2.75f,  0.0f, 1.0f,
	-4.5f, 0.0f,  2.75f,  0.0f, 0.0f,

	-4.5f,  2.5f,  2.75f,  1.0f, 0.0f,	//1тр
	-4.5f,  2.5f, -2.75f,  1.0f, 1.0f,
	-4.5f, 0.0f, -2.75f,  0.0f, 1.0f,
	-4.5f, 0.0f, -2.75f,  0.0f, 1.0f,	//2тр
	-4.5f, 0.0f,  2.75f,  0.0f, 0.0f,
	-4.5f,  2.5f,  2.75f,  1.0f, 0.0f,

	 4.5f,  2.5f,  2.75f,  1.0f, 0.0f,	//1тр
	 4.5f,  2.5f, -2.75f,  1.0f, 1.0f,
	 4.5f, 0.0f, -2.75f,  0.0f, 1.0f,
	 4.5f, 0.0f, -2.75f,  0.0f, 1.0f,	//2тр		
	 4.5f, 0.0f,  2.75f,  0.0f, 0.0f,
	 4.5f,  2.5f,  2.75f,  1.0f, 0.0f,

	-4.5f, 0.0f, -2.75f,  0.0f, 1.0f,	//1тр
	 4.5f, 0.0f, -2.75f,  1.0f, 1.0f,
	 4.5f, 0.0f,  2.75f,  1.0f, 0.0f,
	 4.5f, 0.0f,  2.75f,  1.0f, 0.0f,	//2тр
	-4.5f, 0.0f,  2.75f,  0.0f, 0.0f,
	-4.5f, 0.0f, -2.75f,  0.0f, 1.0f,
	};

	GLuint indices[] =
	{  
		0, 1, 3,																	// 1ый треугольник
		1, 2, 3																		// 2ой треугольник
	};

	//Создание VBO, VAO, EBO
	GLuint  VBO, VAO, EBO;
	//----//																		 
	glGenBuffers(1, &VBO);															//Создаем VBO через эту функцию,											
	glGenVertexArrays(1, &VAO);														//VAO
	glGenBuffers(1, &EBO);															//EBO
	//----//
	glBindVertexArray(VAO);															//Привяз VAO(-> необходимо привзять VBO и указатели на атрибуты к VAO)
	//----//
	glBindBuffer(GL_ARRAY_BUFFER, VBO);												//4)Все данные, которые хотим хранить VBO будут в буфере GL_ARRAY_BUFFER(привяз буфер GL_ARRAY_BUFFER. Теперь любой вызов, использующий буфер, будет работать с VBO.) (GL_ELEMENT_ARRAY_BUFFER используется для обозначения буфера, который)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);										//4)(GL_ELEMENT_ARRAY_BUFFER используется для обозначения буфера, который содержит индексы каждого элемента в буфере GL_ARRAY_BUFFER)
	//----//
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		//4)Копируем наши вершины в буфер для OpenGL.Вызов glBufferData для копирования вершинных данных в этот буфер(копирование данных пользователя в указанный буфер).1аргумент —  тип буфера в который мы хотим скопировать данные (наш VBO сейчас привязан к GL_ARRAY_BUFFER). 2ой - определяет количество данных (в байтах), которые хотим передать буферу. 3 аргумент — это  данные. 4аргумент определяет как мы хотим чтобы видеокарта работала с переданными ей данными(3 режима:GL_STATIC_DRAW: данные либо никогда не будут изменяться(Данные о позиции треугольника меняться не будут), либо будут изменяться очень редко; GL_DYNAMIC_DRAW: данные будут меняться довольно часто;GL_STREAM_DRAW: данные будут меняться при каждой отрисовке) (Данные для видеокарты)). 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//4)Копируем индексы вершин 
	//----//
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);						//5)Атрибут для вершин: Устанавливаем указатели на вершинные атрибуты. 1-ый аргумент - какой параметр шейдера хотим настриоть(position - layout (location = 0)), 2ой аргумент -  размер аргумента(т.к. vec3), 3ий  используемый тип данных, 4ый указывает необходимость нормализовать входные данные(Если укажем GL_TRUE, то все данные будут расположены между 0 (-1 для знаковых значений) и 1. Нормализация не требуется -> оставляем GL_FALSE), 5ый шаг(описывает расстояние между наборами данных), 6ой - имеет тип GLvoid*-> необходимо приведение типов. - ЭТО смещение начала данных в буфере(У нас буфер не имеет смещения и поэтому  указываем 0)
	glEnableVertexAttribArray(0);																			//5)Т.к атрибут вершин отключен -> включить
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));	//5)Атрибут цвета:
	glEnableVertexAttribArray(1);																			//5)Вкл
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));	//5)Атрибут расположения текстуры
	glEnableVertexAttribArray(2);																			//5)Вкл					
	glBindVertexArray(0);															//Отвязываем Vao (далее можно снова привязать "glBindVertexArray(VAO);" и необх снова отвязать) 												
	
	
	GLuint texture1;																				//6)Создание текстур																				
	// Texture 1
	glGenTextures(1, &texture1);																	//6)Создание текстуры (1ый арг - колличество текстур, 2ой - массив идентификаторов текстур)
	glBindTexture(GL_TEXTURE_2D, texture1);															//Привяз
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);									//1ый арг - к чему привязаа текстура(2д - GL_TEXTURE_2D), 2ой арг - опция текстуры(WRAP)(WRAP_S - для оси S), 3ий - метод wrapping(GL_MIRRORED_REPEAT)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);									//WRAP_T - для оси T
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("../Pics/floor.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);		//1ый - текстурная цель(GL_TEXTURE_2D), 2ой - описывает уровень мипмапа для которого мы хотим сгенерировать текстуру(0 - генерация на OPENGL),	3ий - каком формате хранить текстуру, 4ый - ширина, 5ый - высота, 6ой - утсаревший(всегд 0), 7ой - формат изображ(RGB), 8ой - тип данных изображения(т.к. загружали изображение и хранили в байтах (cha)r - GL_UNSIGNED_BYTE), 9ый - изображение
	glGenerateMipmap(GL_TEXTURE_2D);																//Генерация мипмапов
	SOIL_free_image_data(image);																	//Освобожд уч.памяти под изображ	
	glBindTexture(GL_TEXTURE_2D, 0);																//Отвязка объекта текстуры	
	

	Model Table(const_cast<GLchar*>("../Models/Table/Wood_Table.obj"));
	Model Door(const_cast<GLchar*>("../Models/Room-door/Door_Component_BI3.obj"));
	//Model Tree(const_cast<GLchar*>("../Models/Tree/Tree.obj"));
	Model Ref(const_cast<GLchar*>("../Models/refregerator/Refrigerator.obj"));
	//Model Ta(const_cast<GLchar*>("../Models/table2/table3.obj"));
	Model lamp(const_cast<GLchar*>("../Models/lamp/eb_lamp_01.obj"));

	while (!glfwWindowShouldClose(window))											//проверяет, не передано ли указание закончить работу 
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();															//Проверяем события и вызываем функции обратного вызова(вроде ввода с клавиатуры или перемещение мыши) и вызывает установленные функции
		movement();
		glBindVertexArray(VAO);														//Исп Vao	

	//Команды отрисовки ...
		glClearColor(0.5f, 0.3f, 1.0f, 1.0f);										//Цвет окна
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);							//GlClear(<какие биты очистить>) - очистить буфер (GL_COLOR_BUFFER_BIT - цветовой,  GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT )Как только мы вызываем glClear весь буфер будет заполнен указанным 	цветом.glClearColor — это функция устанавливающая состояние, а glClear — это функция использующая состояние
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);

		ourShader.Use();
		
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, .0f, 0.0f));				//применяем матрицу модели, чтобы равзернуть изображение в виде плосоктсти, повернув на 55 градусов, передвая в качестве поворота ОХ (1, 0, 0)														//матрица модели (состоит из сдвигов, масштабирования, поворотов) ->преобразов. все локальные вершины объекта в глобальное мировое пространство
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");			//1)передача матрицы модели в шейдер
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glm::mat4 view = camera.GetViewMatrix();									//матрица камеры (результат преобразования мировых координат в координаты, которые выглядят, как будто пользователь смотрит на них спереди)
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");			//2)передача матрицы вида в шейдер
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glm::mat4 projection;														//матрица проекции
		projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);	//перпективная проекция (Сущ. ортогональная, в которой удаленные предметы не кажутся ближе - исп для 2д). 1ый арг - fov (поле обзора) 45 градусов
		GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");		//3)передача матрицы проекции в шейдер
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glDrawArrays(GL_TRIANGLES, 0, 30);										//Описываем рисуемый примитив GL_TRIANGLES. 2ой аругмент - нач индекс массива  вершин, 3ий количество вершин
	
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

		

		glBindVertexArray(0);													//Отвязываем VAO
	//Конец.

		glfwSwapBuffers(window);												//заменяет цветовой буфер, который использовался для отрисовки во время текущей итерации и показывает результат на экране.
	}
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();															//*очистить выделенные рессурсы
	return 0;
}

