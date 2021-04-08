#pragma once

#include <fstream> 
#include <sstream> 
#include <iostream>
#include <vector>

#include "Shader.h"
#include "Lamp.h"
#include "jalousie.h"

using namespace std;

class ReadFile
{
public:
    ReadFile() {}

    void read_txt(Shader& shader, Lamp& lamp, Jalousie& jalousie);

};
