#pragma once

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
#include <vector>
using namespace std;

class Jalousie
{
public:
    Jalousie();

    int Mode();
    int count_closer_jalousie() const;

    int GetMode(size_t _n) const;
    size_t Get_number_jalousie() const;

private:
    vector<int> mode_j;
    size_t number_jalousie;

};

