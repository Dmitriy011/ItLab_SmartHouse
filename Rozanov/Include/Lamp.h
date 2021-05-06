#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <fstream> 
#include <sstream>

#include <vector>

#include "Shader.h"

using namespace std;
using namespace glm;

class Lamp
{
public:
	vector<int> modes_lights;

    Lamp();

	void init_all_lights(Shader& shader, vec3 pointLightPositions[]);
	void change_brightness_light(Shader& shader, int value, int number_lamp);
	void change_brightness_depended_jalousie(Shader& shader, int count_close_jalousie);

	void on_max_all_lamp(Shader& shader);
	void on_min_all_lamp(Shader& shader);

	string get_light_const() const;
	string get_light_linear() const;
	string get_light_quadratic() const;
	int get_mode_light(int index) const;

private:
	string light_const;
	string light_linear;
	string light_quadratic;
	vector<float> constant_lamp;
	vector<float> linear_lamp;
	vector<float> quadratic_lamp;

	

	void init_brightness_constants(size_t _number);
};
