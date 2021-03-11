#pragma once

#include <fstream> 
#include <sstream> 
#include <iostream>

using namespace std;

class ReadFile
{
public:
    void read_txt();

    string GetValue();

    size_t Get_numbers_lamp();

private:
    string value;
    size_t number_lamps;
};
