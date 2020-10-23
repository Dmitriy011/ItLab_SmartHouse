// GLEW нужно подключать до GLFW.
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include "SomeFunc.h"
#include "Shader.h"

#include <iostream>

const GLuint WIDTH = 800, HEIGHT = 600;												//Размер окна

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

	//Сообщить Opengl размер окна
	int width;
	int height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);												//glViewport(<позиция нижнего левого угла экрана1>, <позиция нижнего левого угла экрана2>, <ширина>, <высота>);
	//проверка, что инцилизируется.
	if (glewInit() != GLEW_OK)
	{
		return 1;
	}
	glewInit();																		//Инцилизируется после создания текущего контекста glfwMakeContextCurrent 

	glfwSetKeyCallback(window, key_callback);										//Передаем сущ-е ф-ии в GLWF

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

	//Создание EBO, VAO, EBO
	GLuint  VBO, VAO, EBO;
	glGenBuffers(1, &VBO);															//3)Создаем VBO через эту функцию
	glGenVertexArrays(1, &VAO);														//3)Создаем VAO через эту функцию(Привяз для использования)	->нужно настроить требуемые VBO и указатели на атрибуты, а в конце отвязать VAO для последующего использования. Каждый раз когда мы хотим отрисовать объект мы просто привязываем VAO с требуемыми нам настройками перед отрисовкой объекта
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);															//Привяз VAO (-> необходимо привзять VBO и указатели на атрибуты к VAO)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);												//4)Копируем наши вершины в буфер для OpenGL(привяз буфер GL_ARRAY_BUFFER. Теперь любой вызов, использующий буфер, будет работать с VBO. )
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		//4)Копируем наши вершины в буфер для OpenGL.Вызов glBufferData для копирования вершинных данных в этот буфер(копирование данных пользователя в указанный буфер).1аргумент —  тип буфера в который мы хотим скопировать данные (наш VBO сейчас привязан к GL_ARRAY_BUFFER). 2аргумент определяет количество данных (в байтах), которые хотим передать буферу. 3 аргумент — это  данные. 4аргумент определяет как мы хотим чтобы видеокарта работала с переданными ей данными(3 режима:GL_STATIC_DRAW: данные либо никогда не будут изменяться(Данные о позиции треугольника меняться не будут), либо будут изменяться очень редко; GL_DYNAMIC_DRAW: данные будут меняться довольно часто;GL_STREAM_DRAW: данные будут меняться при каждой отрисовке) (Данные для видеокарты)). 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);//5)Устанавливаем указатели на вершинные атрибуты. 1-ый аргумент - какой параметр шейдера хотим настриоть(position - layout (location = 0)), 2ой аргумент -  размер аргумента(т.к. vec3), 3ий  используемый тип данных, 4ый указывает необходимость нормализовать входные данные(Если укажем GL_TRUE, то все данные будут расположены между 0 (-1 для знаковых значений) и 1. Нормализация не требуется -> оставляем GL_FALSE), 5ый шаг(описывает расстояние между наборами данных), 6ой - имеет тип GLvoid*-> необходимо приведение типов. - ЭТО смещение начала данных в буфере(У нас буфер не имеет смещения и поэтому  указываем 0)
	glEnableVertexAttribArray(0);													//5)Т.к атрибут вершин отключен -> включить
	glBindVertexArray(0);															//Отвязываем Vao (далее можно снова привязать "glBindVertexArray(VAO);" и необх снова отвязать) 												
	
	Shader ourShader("../Shader/Vertex/Vertex.txt", "../Shader/Fragment/fragment.txt ");

	while (!glfwWindowShouldClose(window))											//проверяет, не передано ли указание закончить работу 
	{
		glfwPollEvents();															//Проверяем события и вызываем функции обратного вызова(вроде ввода с клавиатуры или перемещение мыши) и вызывает установленные функции
		
	//Команды отрисовки ...
		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);										//Цвет окна
		glClear(GL_COLOR_BUFFER_BIT);												//GlClear(<какие биты очистить>) - очистить буфер (GL_COLOR_BUFFER_BIT - цветовой,  GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT )Как только мы вызываем glClear весь буфер будет заполнен указанным 	цветом.glClearColor — это функция устанавливающая состояние, а glClear — это функция использующая состояние
		
		ourShader.Use();
		GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		GLint vertexColorLocation = glGetUniformLocation(ourShader.Program, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		
		glUseProgram(ourShader.Program);
		glBindVertexArray(VAO);		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);								// 1ый ар. - г что мы хотим отрисовывать переднюю и заднюю части всех треугольников, а 2ой-  что мы хотим отрисовывать только линии. Для того, чтобы вернуться к начальной конфигурации  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL).
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);											//Описываем рисуемый примитив GL_TRIANGLES. 2ой аругмент - нач индекс массива  вершин, 3ий количество вершин
		glBindVertexArray(0);														//Отвязываем VAO
	//Конец.

		glfwSwapBuffers(window);													//заменяет цветовой буфер, который использовался для отрисовки во время текущей итерации и показывает результат на экране.
	}

	glfwTerminate();																//*очистить выделенные рессурсы


	return 0;
}
