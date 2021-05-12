#include "Lamp.h"

Lamp::Lamp()
{
	light_const = "";
	light_linear = "";
	light_quadratic = "";

    constant_lamp = { 1.0f };
    linear_lamp = { 0.7f, 0.35f, 0.22f, 0.14f, 0.09f, 0.07f, 0.045f, 0.027f, 0.022f, 0.014f, 0.007f, 0.0014f };
    quadratic_lamp = { 1.8f, 0.44f, 0.20f, 0.07f, 0.032f, 0.017f, 0.0075f, 0.0028f, 0.0019f, 0.0007f, 0.0002f, 0.000007f };

    for (int i = 0; i < 13; i++)
    {
        modes_lights.push_back(0);
    }
}

void Lamp::init_all_lights(Shader& shader, vec3 pointLightPositions[])
{
    string tmp1;
    string tmp2;
    string tmp3;
    string tmp4;

    for (size_t i = 0; i < 13; i++)
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

void Lamp::change_brightness_light(Shader& shader, int value, int number_lamp)
{
    shader.setFloat(light_const, constant_lamp[0]);
    shader.setFloat(light_linear,linear_lamp[value]);
    shader.setFloat(light_quadratic, quadratic_lamp[value]);

    modes_lights[number_lamp - 1] = value;
    init_brightness_constants(number_lamp);
}

void Lamp::change_brightness_depended_jalousie(Shader& shader, int count_close_jalousie)
{
    switch (count_close_jalousie)
    {
    case 1:
    {
        modes_lights[12] = 8;

        break;
    }
    case 2:
    {
        modes_lights[12] = 6;

        break;
    }
    case 3:
    {
        modes_lights[12] = 3;

        break;
    }
    case 4:
    {
        modes_lights[12] = 0;

        break;
    }
    case 0:
    {
        modes_lights[12] = 11;

        break;
    }
    }

    shader.setFloat(light_const, constant_lamp[0]);
    shader.setFloat(light_linear, linear_lamp[modes_lights[12]]);
    shader.setFloat(light_quadratic, quadratic_lamp[modes_lights[12]]);

    init_brightness_constants(13);
}

void Lamp::on_max_all_lamp(Shader& shader)
{
    string tmp1;
    string tmp2;
    string tmp3;
    string tmp4;

    for (size_t i = 0; i < 12; i++)
    {
        tmp1 = "pointLights[";
        tmp2 = to_string(i);
        tmp1.append(tmp2);
        tmp3 = "].constant";
        tmp4 = tmp1;
        tmp4.append(tmp3);
        shader.setFloat(tmp4, constant_lamp[0]);

        tmp3 = "].linear";
        tmp4 = tmp1;
        tmp4.append(tmp3);
        shader.setFloat(tmp4, linear_lamp[11]);

        tmp3 = "].quadratic";
        tmp4 = tmp1;
        tmp4.append(tmp3);
        shader.setFloat(tmp4, quadratic_lamp[11]);
    }

    shader.setFloat("pointLights[12].constant", constant_lamp[0]);
    shader.setFloat("pointLights[12].linear", linear_lamp[11]);
    shader.setFloat("pointLights[12].quadratic", quadratic_lamp[11]);
}

void Lamp::on_min_all_lamp(Shader& shader)
{
    string tmp1;
    string tmp2;
    string tmp3;
    string tmp4;

    for (size_t i = 0; i < 12; i++)
    {
        tmp1 = "pointLights[";
        tmp2 = to_string(i);
        tmp1.append(tmp2);
        tmp3 = "].constant";
        tmp4 = tmp1;
        tmp4.append(tmp3);
        shader.setFloat(tmp4, constant_lamp[0]);

        tmp3 = "].linear";
        tmp4 = tmp1;
        tmp4.append(tmp3);
        shader.setFloat(tmp4, linear_lamp[0]);

        tmp3 = "].quadratic";
        tmp4 = tmp1;
        tmp4.append(tmp3);
        shader.setFloat(tmp4, quadratic_lamp[0]);
    }

    shader.setFloat("pointLights[12].constant", 1.8f);
    shader.setFloat("pointLights[12].linear", 0.0014f);
    shader.setFloat("pointLights[12].quadratic", 0.000007f);
}

string Lamp::get_light_const() const
{
    return light_const;
}

string Lamp::get_light_linear() const
{
    return light_linear;
}

string Lamp::get_light_quadratic() const
{
    return light_quadratic;
}

int Lamp::get_mode_light(int index) const
{
    return modes_lights[index];
}

void Lamp::init_brightness_constants(size_t _number)
{
    string tmp1;
    string tmp2;
    string tmp3;
    string tmp4;

    tmp1 = "pointLights[";
    tmp2 = to_string(_number - 1);
    tmp1.append(tmp2);
    tmp3 = "].constant";
    tmp4 = tmp1;
    tmp4.append(tmp3);
    light_const = tmp4;

    tmp3 = "].linear";
    tmp4 = tmp1;
    tmp4.append(tmp3);
    light_linear = tmp4;

    tmp3 = "].quadratic";
    tmp4 = tmp1;
    tmp4.append(tmp3);
    light_quadratic = tmp4;
}
