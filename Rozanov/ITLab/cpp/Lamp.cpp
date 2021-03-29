#include "Lamp.h"

Lamp::Lamp()
{
	light_const = "";
	light_linear = "";
	light_quadratic = "";
}

void Lamp::init_all_lamp(Shader& shader, vec3 pointLightPositions[])
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

void Lamp::brightness(Shader& shader)
{
    ReadFile brightnes;
    brightnes.read_txt();

    string tmp = brightnes.GetValueL();
    size_t numbers_lamp = brightnes.Get_numbers_lamp();

    switch (stoi(brightnes.GetValueL()))
    {
    case 0:
    {
        shader.setFloat(light_const, 1.0f);
        shader.setFloat(light_linear, 0.7f);
        shader.setFloat(light_quadratic, 1.8f);

        break;
    }
    case 1:
    {
        shader.setFloat(light_const, 1.0f);
        shader.setFloat(light_linear, 0.35f);
        shader.setFloat(light_quadratic, 0.44f);
        break;
    }
    case 2:
    {

        shader.setFloat(light_const, 1.0f);
        shader.setFloat(light_linear, 0.22f);
        shader.setFloat(light_quadratic, 0.20f);
        break;
    }
    case 3:
    {
        shader.setFloat(light_const, 1.0f);
        shader.setFloat(light_linear, 0.14f);
        shader.setFloat(light_quadratic, 0.07f);
        break;
    }
    case 4:
    {

        shader.setFloat(light_const, 1.0f);
        shader.setFloat(light_linear, 0.09f);
        shader.setFloat(light_quadratic, 0.032f);
        break;
    }
    case 5:
    {

        shader.setFloat(light_const, 1.0f);
        shader.setFloat(light_linear, 0.07f);
        shader.setFloat(light_quadratic, 0.017f);
        break;
    }
    case 6:
    {
        shader.setFloat(light_const, 1.0f);
        shader.setFloat(light_linear, 0.045f);
        shader.setFloat(light_quadratic, 0.0075f);
        break;
    }
    case 7:
    {
        shader.setFloat(light_const, 1.0f);
        shader.setFloat(light_linear, 0.027f);
        shader.setFloat(light_quadratic, 0.0028f);
        break;
    }
    case 8:
    {
        shader.setFloat(light_const, 1.0f);
        shader.setFloat(light_linear, 0.022f);
        shader.setFloat(light_quadratic, 0.0019f);
        break;
    }
    case 9:
    {
        shader.setFloat(light_const, 1.0f);
        shader.setFloat(light_linear, 0.014f);
        shader.setFloat(light_quadratic, 0.0007f);
        break;
    }
    case 10:
    {
        shader.setFloat(light_const, 1.0f);
        shader.setFloat(light_linear, 0.007f);
        shader.setFloat(light_quadratic, 0.0002f);
        break;
    }
    case 11:
    {
        shader.setFloat(light_const, 1.0f);
        shader.setFloat(light_linear, 0.0014f);
        shader.setFloat(light_quadratic, 0.000007f);
        break;
    }
    }

    init_brightness_constants(numbers_lamp);
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

void Lamp::on_max_all_lamp(Shader& shader)
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
        tmp3 = "].constant";
        tmp4 = tmp1;
        tmp4.append(tmp3);
        shader.setFloat(tmp4, 1.0f);

        tmp3 = "].linear";
        tmp4 = tmp1;
        tmp4.append(tmp3);
        shader.setFloat(tmp4, 0.0014f);

        tmp3 = "].quadratic";
        tmp4 = tmp1;
        tmp4.append(tmp3);
        shader.setFloat(tmp4, 0.000007f);
    }
}

void Lamp::on_min_all_lamp(Shader& shader)
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
        tmp3 = "].constant";
        tmp4 = tmp1;
        tmp4.append(tmp3);
        shader.setFloat(tmp4, 1.0f);

        tmp3 = "].linear";
        tmp4 = tmp1;
        tmp4.append(tmp3);
        shader.setFloat(tmp4, 0.7f);

        tmp3 = "].quadratic";
        tmp4 = tmp1;
        tmp4.append(tmp3);
        shader.setFloat(tmp4, 1.8f);
    }
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
