#pragma once

#include "Shader.h"
#include "ReadFile.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <fstream> 
#include <sstream>

using namespace std;
using namespace glm;

class Lamp
{
public:
    Lamp();

	void init_all_lamp(Shader& shader, vec3 pointLightPositions[]);
	void brightness(Shader& shader);
    void init_brightness_constants(size_t _number);
	void on_max_all_lamp(Shader& shader);

	string get_light_const();
	string get_light_linear();
	string get_light_quadratic();

private:
	string light_const;
	string light_linear;
	string light_quadratic;
};
