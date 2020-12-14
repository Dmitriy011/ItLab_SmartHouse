#pragma once

#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Intilization_value
{
public:
	bool keys[1024];
	//----// ƒл€ разных комьютеров сокрость передвижени€ разна€ -> вычисл врем€ затраченное на визуализацию и от него зависит скорость
	GLfloat deltaTime;															// врем€, затраченное на визуализацию последнего выведенного кадра
	GLfloat lastFrame;															// врем€ вывода последнего кадра
	GLfloat lastX;
	GLfloat	lastY;
	bool firstMouse;

	Intilization_value();

	void intilization_libs()
	{
		//»нициализаци€ GLFW. Ќастройка GLFW
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);									//glfwWindowHint(<идентификатор параметра, который подвергаетс€ изменению>, <значение, которое устанавливаетс€ соответствующему параметру>).GLFW_CONTEXT_VERSION_MAJOR и GLFW_CONTEXT_VERSION_MINOR указывают версию клиентского API(программного интерфейса приложени€), с которым должен быть совместим созданный контекст
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);					//GLFW_OPENGL_PROFILE указывает, дл€ какого профил€ OpenGL создать контекст.(GLFW_OPENGL_CORE_PROFILE или GLFW_OPENGL_COMPAT_PROFILE или GLFW_OPENGL_ANY_PROFILE, чтобы не запрашивать конкретный профиль. ≈сли запрашиваетс€ верси€ OpenGL ниже 3.2, необходимо использовать GLFW_OPENGL_ANY_PROFIL)
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glViewport(0, 0, WIDTH, HEIGHT);												//—ообщить Opengl размер окна - glViewport(<позици€ нижнего левого угла экрана1>, <позици€ нижнего левого угла экрана2>, <ширина>, <высота>);
	}

	int intilization_glew()
	{
		//проверка, что инцилизируетс€.
		if (glewInit() != GLEW_OK)
		{
			return 1;
		}
		glewInit();																		//»нцилизируетс€ после создани€ текущего контекста glfwMakeContextCurrent 
	}

	void settings()
	{
		glEnable(GL_DEPTH_TEST);														//¬кл, чтобы OpenGL  выполн€л проверку глубины, включа€ парамтер параметр GL_DEPTH_TEST	
	}

	glm::vec3 GetlightPos();
	GLuint GetWidht();
	GLuint GetHeight();
	
private:
	glm::vec3 lightPos;
	GLuint WIDTH;
	GLuint HEIGHT;
};