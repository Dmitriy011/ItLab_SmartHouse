#include "ReadFile.h"

ReadFile::ReadFile()
{
    value_l = "0";
    value_j = "0";
}

void ReadFile::read_txt()
{
    string filename = "..\\..\\Uglinskiy\\Smart_House\\Smart_House\\smart_lamp.txt";
    //string filename = "D:\\labs\\ItLab\\ItLab_SmartHouse\\Rozanov\\MyInfo\\myInfo.txt";

    string tmp = "";
    ifstream fin;
    string lastLine = "";
    string buf;
    fin.open(filename);
    while (std::getline(fin, buf, '\n'))
    {
        lastLine = buf;
    }

    switch (lastLine[0])
    {
    case 'l':
    {
        tmp.push_back(lastLine[5]);
        number_lamps = stoi(tmp);
        if (lastLine.find_last_of(';') == 14)
        {
            value_l.push_back(lastLine[12]);
            value_l.push_back(lastLine[13]);
        }
        if (lastLine.find_last_of(';') == 13)
        {
            value_l.push_back(lastLine[12]);
        }
    }
    case 'j':
    {
        tmp.push_back(lastLine[9]);
        number_jalousie = stoi(tmp);
        if (lastLine.find_last_of(';') == 16)
        {
            value_j.push_back(lastLine[15]);
        }
        if (lastLine.find_last_of(';') == 17)
        {
            value_j.push_back(lastLine[15]);
            value_j.push_back(lastLine[16]);
        }
    }
    }
    
}

string ReadFile::GetValueL()
{
    return value_l;
}

string ReadFile::GetValueJ()
{
    return value_j;
}

size_t ReadFile::Get_numbers_lamp()
{
    return number_lamps;
}

size_t ReadFile::Get_number_jalousie()
{
    return number_jalousie;
}
