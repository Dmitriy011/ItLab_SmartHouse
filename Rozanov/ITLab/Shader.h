#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glew.h>

class Shader
{
public:   
    GLuint Program;

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = nullptr);

    void Use();
};