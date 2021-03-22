#include "Intilization.h"

Intilization::Intilization()
{
	WIDTH = 800;												//размер окна
	HEIGHT = 600;												//размер окна
	lastX = 400;
	lastY = 300;
	firstMouse = true;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
}

void Intilization::intilization_libs()
{
	//Инициализация GLFW. Настройка GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);									//glfwWindowHint(<идентификатор параметра, который подвергается изменению>, <значение, которое устанавливается соответствующему параметру>).GLFW_CONTEXT_VERSION_MAJOR и GLFW_CONTEXT_VERSION_MINOR указывают версию клиентского API(программного интерфейса приложения), с которым должен быть совместим созданный контекст
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);					//GLFW_OPENGL_PROFILE указывает, для какого профиля OpenGL создать контекст.(GLFW_OPENGL_CORE_PROFILE или GLFW_OPENGL_COMPAT_PROFILE или GLFW_OPENGL_ANY_PROFILE, чтобы не запрашивать конкретный профиль. Если запрашивается версия OpenGL ниже 3.2, необходимо использовать GLFW_OPENGL_ANY_PROFIL)
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glViewport(0, 0, WIDTH, HEIGHT);												//Сообщить Opengl размер окна - glViewport(<позиция нижнего левого угла экрана1>, <позиция нижнего левого угла экрана2>, <ширина>, <высота>);

}

int Intilization::intilization_glew()
{
	//проверка, что инцилизируется.
	if (glewInit() != GLEW_OK)
	{
		return 1;
	}
	glewInit();																		//Инцилизируется после создания текущего контекста glfwMakeContextCurrent 
}

void Intilization::settings()
{
	glEnable(GL_DEPTH_TEST);														//Вкл, чтобы OpenGL  выполнял проверку глубины, включая парамтер параметр GL_DEPTH_TEST	
}

GLuint Intilization::GetWidht() const
{
	return WIDTH;
}

GLuint Intilization::GetHeight() const
{
	return HEIGHT;
}

GLfloat Intilization::GetDeltaTime() const
{
	return deltaTime;
}

GLfloat Intilization::GetLastFrame() const
{
	return lastFrame;
}

GLfloat Intilization::GetLastX() const
{
	return lastX;
}

GLfloat Intilization::GetLastY() const
{
	return lastY;
}

bool Intilization::GetFirstMouse() const
{
	return firstMouse;
}

void Intilization::SetDeltaTime(GLfloat _v)
{
	deltaTime = _v;
}

void Intilization::SetLastFrame(GLfloat _v)
{
	lastFrame = _v;
}

void Intilization::SetLastX(GLfloat _v)
{
	lastX = _v;
}

void Intilization::SetLastY(GLfloat _v)
{
	lastY = _v;
}

void Intilization::SetFirstMouse(bool _v)
{
	firstMouse = _v;
}
