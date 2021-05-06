#pragma once

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

using namespace std;

class Jalousie
{
public:
    vector<int> mode_j;

    Jalousie();

    int init_mode_jalousie(size_t number_jalousie, int value);
    
    int Get_count_closer_jalousie() const;
    int GetMode(size_t _n) const;

private:
    
};

