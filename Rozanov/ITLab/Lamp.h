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

class Lamp
{
public:
    Lamp();

	void init_all_lamp(Shader& shader, glm::vec3 pointLightPositions[])
	{
        string tmp1;
        string tmp2;
        string tmp3;
        string tmp4;

        for (size_t i = 0; i < 4; i++)
        {
            tmp1 = "pointLights[";
            tmp2 = to_string(i);
            tmp1.append(tmp2);
            tmp3 = "].position";
            tmp4 = tmp1;
            tmp4.append(tmp3);
            shader.setVec3(tmp4, pointLightPositions[i]);

            tmp3 = "].ambient";
            tmp4 = tmp1;
            tmp4.append(tmp3);
            shader.setVec3(tmp4, 0.1f, 0.1f, 0.1f);

            tmp3 = "].diffuse";
            tmp4 = tmp1;
            tmp4.append(tmp3);
            shader.setVec3(tmp4, 0.4f, 0.4f, 0.4f);

            tmp3 = "].specular";
            tmp4 = tmp1;
            tmp4.append(tmp3);
            shader.setVec3(tmp4, 1.0f, 1.0f, 1.0f);
        }
	}

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
