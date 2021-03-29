#pragma once

#include <fstream> 
#include <sstream> 
#include <iostream>
#include <vector>

using namespace std;


class ReadFile
{
public:
    ReadFile();

    void read_txt();

    string GetValueL();
    string GetValueJ();

    size_t Get_numbers_lamp();
    size_t Get_number_jalousie();

private:
    string value_l;
    string value_j;
    size_t number_lamps;
    size_t number_jalousie;
};
