#pragma once

// GLEW ����� ���������� �� GLFW.
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);