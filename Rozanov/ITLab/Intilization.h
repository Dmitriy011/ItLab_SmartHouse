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
	//----// Для разных комьютеров сокрость передвижения разная -> вычисл время затраченное на визуализацию и от него зависит скорость
	GLfloat deltaTime;															// время, затраченное на визуализацию последнего выведенного кадра
	GLfloat lastFrame;															// время вывода последнего кадра
	GLfloat lastX;
	GLfloat	lastY;
	bool firstMouse;

	Intilization();

	void intilization_libs();

	int intilization_glew()
	{
		//проверка, что инцилизируется.
		if (glewInit() != GLEW_OK)
		{
			return 1;
		}
		glewInit();																		//Инцилизируется после создания текущего контекста glfwMakeContextCurrent 
	}

	void settings()
	{
		glEnable(GL_DEPTH_TEST);														//Вкл, чтобы OpenGL  выполнял проверку глубины, включая парамтер параметр GL_DEPTH_TEST	
	}

	GLuint GetWidht();
	GLuint GetHeight();

private:
	GLuint WIDTH;
	GLuint HEIGHT;
};