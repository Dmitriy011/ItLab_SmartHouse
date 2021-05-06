// GLEW ����� ���������� �� GLFW.
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>

#include "Utils.h"
#include "Shader.h"
#include "Camera.h"
#include "Intilization.h"
#include "MyHouse.h"

#include <iostream> 

using namespace std;
using namespace glm;

Intilization intilizaton;
Camera camera(vec3(0.0f, 0.0f, 3.0f));

int main(int argc, char** argv)														//argc ����� ����������, argv ������ ����������
{
	intilizaton.intilization_libs();
	GLFWwindow* window = glfwCreateWindow(1280, 1024, "Smart House", nullptr, nullptr);		//������, ������. ���������� ��������� �� ������ ���� GLFWwindow
	if (window == nullptr)															//�������� �� ��������
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();															//�������� ��������		
		return -1;
	}
	glfwMakeContextCurrent(window);													//window -������� ��������
	intilizaton.intilization_glew();
	intilizaton.settings();
	
	Utils utils;
	glfwSetKeyCallback(window, key_callback);									//�������� ���-�� �-�� � GLWF
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);				//������ ������� ���� ��� ����.
	glfwSetCursorPosCallback(window, mouse_callback);							//�������� ���-�� �-�� � GLWF
	
	Shader ObjectShader("../Shader/Vertex/Vertex_model.txt", "../Shader/Fragment/fragment_model.txt ");
	Shader LampShader("../Shader/Vertex/Vertex_lamp.txt", "../Shader/Fragment/fragment_lamp.txt ");
	Shader skyboxShader("../Shader/Vertex/Vertex_skybox.txt", "../Shader/Fragment/fragment_skybox.txt");

	MyHouse house;
	house.init_cube_room();
	house.init_skybox();
	house.init_cube_light();
	house.init_texture_cube_room(ObjectShader);
	house.Draw(utils, ObjectShader, LampShader, window, skyboxShader);


	return 0;
}




