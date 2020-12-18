#pragma once

// GLEW нужно подключать до GLFW.
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream> 
#include <sstream> 
#include <time.h>

#include "Camera.h"
#include "Shader.h"

#include "Intilization.h"

#include "ReadFile.h"

using namespace std;

extern Intilization intilizaton;
extern Camera camera;

class Utils
{
public:
	void movement();

	void brightnes(Shader& shader);
};

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);



