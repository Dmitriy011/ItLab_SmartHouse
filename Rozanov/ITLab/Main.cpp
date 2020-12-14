// GLEW нужно подключать до GLFW.
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
#include "Intilization_value.h"
#include "MyRoom.h"

#include <iostream> 

#include <SOIL.h>

using namespace std;

Intilization_value intilize;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main(int argc, char** argv)														//argc число аргументов, argv массив аргументов
{
	intilize.intilization_libs();
	GLFWwindow* window = glfwCreateWindow(800, 600, "Room1", nullptr, nullptr);		//ширина, высота. Возвращает указатель на объект типа GLFWwindow
	if (window == nullptr)															//проверка на создание
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();															//Очистить рессурсы		
		return -1;
	}
	glfwMakeContextCurrent(window);													//window -текущий контекст
	intilize.intilization_glew();
	intilize.settings();
	
	Utils utils;
	glfwSetKeyCallback(window, key_callback);									//Передаем сущ-ие ф-ии в GLWF
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);					//Захват курсора мыши для окна.
	glfwSetCursorPosCallback(window, mouse_callback);							//Передаем сущ-ие ф-ии в GLWF
	
	Shader ObjectShader("../Shader/Vertex/Vertex_model.txt", "../Shader/Fragment/fragment_model.txt ");
	Shader LampShader("../Shader/Vertex/Vertex_lamp.txt", "../Shader/Fragment/fragment_lamp.txt ");
	
	MyRoom room;
	room.create_RoomAndLight();
	ObjectShader.Use();
	glUniform1i(glGetUniformLocation(ObjectShader.Program, "material.diffuse"), 0);

	Model Door(const_cast<GLchar*>("../Models/Room-door/Door_Component_BI3.obj"));

	while (!glfwWindowShouldClose(window))											//проверяет, не передано ли указание закончить работу 
	{
		GLfloat currentFrame = glfwGetTime();
		intilize.deltaTime = currentFrame - intilize.lastFrame;
		intilize.lastFrame = currentFrame;

		glfwPollEvents();															//Проверяем события и вызываем функции обратного вызова(вроде ввода с клавиатуры или перемещение мыши) и вызывает установленные функции
		utils.movement();

		glClearColor(0.5f, 0.3f, 1.0f, 1.0f);										//Цвет окна
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);							//GlClear(<какие биты очистить>) - очистить буфер (GL_COLOR_BUFFER_BIT - цветовой,  GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT )Как только мы вызываем glClear весь буфер будет заполнен указанным 	цветом.glClearColor — это функция устанавливающая состояние, а glClear — это функция использующая состояние

	//Команды отрисовки ...
		
		ObjectShader.Use();
		utils.brighness(ObjectShader);
		ObjectShader.setVec3("light.position", intilize.GetlightPos());
		ObjectShader.setVec3("viewPos", camera.Position);
		ObjectShader.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
		ObjectShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		ObjectShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		ObjectShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		ObjectShader.setFloat("material.shininess", 64.0f);
		glm::mat4 projection = glm::perspective(45.0f, (float)intilize.GetWidht() / (float)intilize.GetWidht(), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		ObjectShader.setMat4("projection", projection);
		ObjectShader.setMat4("view", view);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f, 1.5f, 2.5f));
		ObjectShader.setMat4("model", model);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, room.diffuseMap);
		glBindVertexArray(room.objectVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		model = glm::mat4(1.0f);
		
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-1.4f, -0.55f, 0.6f));
		model = glm::rotate(model, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		ObjectShader.setMat4("model", model);
		Door.Draw(ObjectShader);

		LampShader.Use();
		LampShader.setMat4("projection", projection);
		LampShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, intilize.GetlightPos());
		model = glm::rotate(model, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0, 0.1, 0.1));
		LampShader.setMat4("model", model);
		glBindVertexArray(room.lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	//Конец.

		glfwSwapBuffers(window);												//заменяет цветовой буфер, который использовался для отрисовки во время текущей итерации и показывает результат на экране.
	}

	
	glfwTerminate();															//*очистить выделенные рессурсы
	return 0;
}