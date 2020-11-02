#pragma once

// GLEW нужно подключать до GLFW.
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

extern Camera camera;
extern bool keys[1024];
extern GLfloat lastX;
extern GLfloat lastY;
extern bool firstMouse;
extern GLfloat deltaTime;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void movement();

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
