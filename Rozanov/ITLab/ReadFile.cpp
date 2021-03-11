#include "ReadFile.h"

void ReadFile::read_txt()
{
    //string filename = "..\\..\\Uglinskiy\\SmartHouse\\smart_lamp.txt";
    string filename = "D:\\labs\\ItLab\\ItLab_SmartHouse\\Rozanov\\test\\test.txt";

    string tmp = "";
    ifstream fin;
    string lastLine = "";
    string buf;
    fin.open(filename);
    while (std::getline(fin, buf, '\n'))
    {
        lastLine = buf;
    }

    if (lastLine == "")
    {
        cout << "EMPTY STR";
    }

    tmp.push_back(lastLine[5]);
    number_lamps = stoi(tmp);
    if (lastLine.find_last_of(';') == 14)
    {
        value.push_back(lastLine[12]);
        value.push_back(lastLine[13]);
    }
    if (lastLine.find_last_of(';') == 13)
    {
        value.push_back(lastLine[12]);
    }
}

string ReadFile::GetValue()
{
    return value;
}

size_t ReadFile::Get_numbers_lamp()
{
    return number_lamps;
}
