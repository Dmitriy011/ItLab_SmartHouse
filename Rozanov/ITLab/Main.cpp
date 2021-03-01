// GLEW ����� ���������� �� GLFW.
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Mesh.h"
#include "Intilization.h"
#include "MyRoom.h"

#include <iostream> 

#include <SOIL.h>

using namespace std;

Intilization intilizaton;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main(int argc, char** argv)														//argc ����� ����������, argv ������ ����������
{
	intilizaton.intilization_libs();
	GLFWwindow* window = glfwCreateWindow(800, 600, "Room1", nullptr, nullptr);		//������, ������. ���������� ��������� �� ������ ���� GLFWwindow
	if (window == nullptr)															//�������� �� ��������
	{
		std::cout << "Failed to create GLFW window" << std::endl;
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
	
	MyRoom room;
	room.create_cube_room();
	room.create_cube_light();
	room.crete_texture_cube_room(ObjectShader);
	room.Draw(utils, ObjectShader, LampShader, window);

	return 0;
}