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

using namespace std;

class Jalousie
{
public:
    Jalousie()
    {
        mode1 = 0;
        mode2 = 0;
        number_jalousie = 0;
    }

    int Mode()
    {
        ReadFile jalousie;

        jalousie.read_txt();
        number_jalousie = jalousie.Get_number_jalousie();

        switch (number_jalousie)
        {
        case 1:
        {
            mode1 = stoi(jalousie.GetValueJ());
            break;
        }
        case 2:
        {
            mode2 = stoi(jalousie.GetValueJ());;
            break;
        }
        }

        return GetMode(number_jalousie);
    }

    int GetMode(size_t _n) const
    {
        switch (_n)
        {
        case 1:
        {
            return mode1;
        }
        case 2:
        {
            return mode2;
        }
        }
    }

    size_t Get_number_jalousie() const
    {
        return number_jalousie;
    }

private:
    int mode1;
    int mode2;
    size_t number_jalousie;

};

