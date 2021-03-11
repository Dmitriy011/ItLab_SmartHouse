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
	//»нициализаци€ GLFW. Ќастройка GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);									//glfwWindowHint(<идентификатор параметра, который подвергаетс€ изменению>, <значение, которое устанавливаетс€ соответствующему параметру>).GLFW_CONTEXT_VERSION_MAJOR и GLFW_CONTEXT_VERSION_MINOR указывают версию клиентского API(программного интерфейса приложени€), с которым должен быть совместим созданный контекст
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);					//GLFW_OPENGL_PROFILE указывает, дл€ какого профил€ OpenGL создать контекст.(GLFW_OPENGL_CORE_PROFILE или GLFW_OPENGL_COMPAT_PROFILE или GLFW_OPENGL_ANY_PROFILE, чтобы не запрашивать конкретный профиль. ≈сли запрашиваетс€ верси€ OpenGL ниже 3.2, необходимо использовать GLFW_OPENGL_ANY_PROFIL)
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glViewport(0, 0, WIDTH, HEIGHT);												//—ообщить Opengl размер окна - glViewport(<позици€ нижнего левого угла экрана1>, <позици€ нижнего левого угла экрана2>, <ширина>, <высота>);

}

GLuint Intilization::GetWidht()
{
	return WIDTH;
}

GLuint Intilization::GetHeight()
{
	return HEIGHT;
}
