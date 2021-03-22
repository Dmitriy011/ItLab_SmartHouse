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

	Intilization();
	void intilization_libs();
	int intilization_glew();
	void settings();

	GLuint GetWidht() const;
	GLuint GetHeight() const;
	GLfloat GetDeltaTime() const;
	GLfloat GetLastFrame() const;
	GLfloat GetLastX() const;
	GLfloat	GetLastY() const;
	bool GetFirstMouse() const;

	void SetDeltaTime(GLfloat _v);
	void SetLastFrame(GLfloat _v);
	void SetLastX(GLfloat _v);
	void SetLastY(GLfloat _v);
	void SetFirstMouse(bool _v);

private:
	GLuint WIDTH;
	GLuint HEIGHT;
	//----// Для разных комьютеров сокрость передвижения разная -> вычисл время затраченное на визуализацию и от него зависит скорость
	GLfloat deltaTime;															// время, затраченное на визуализацию последнего выведенного кадра
	GLfloat lastFrame;															// время вывода последнего кадра
	GLfloat lastX;
	GLfloat	lastY;
	bool firstMouse;

	
};