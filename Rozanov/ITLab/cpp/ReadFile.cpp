#include "ReadFile.h"

ReadFile::ReadFile()
{
    value_l = "0";
    value_j = "0";
    number_jalousie = 1;
    number_lamps = 1;
}

void ReadFile::read_txt()
{
    string filename = "..\\..\\Uglinskiy\\Smart_House\\Smart_House\\smart_lamp.txt";
    //string filename = "D:\\to_add\\Rozanov\\MyInfo\\myInfo.txt";
    int tmp1 = 0;
    string tmp = "";
    ifstream fin;
    string lastLine = "";
    string buf;
    fin.open(filename);

    while (std::getline(fin, buf, '\n'))
    {
        lastLine = buf;
        tmp1++;
    }

    switch (lastLine[0])
    {
    case 'l':
    {
        if (lastLine[7] == '_')
        {
            tmp.push_back(lastLine[5]);
            tmp.push_back(lastLine[6]);
            number_lamps = stoi(tmp);
            if (lastLine.find_last_of(';') == 15)
            {
                value_l.push_back(lastLine[13]);
                value_l.push_back(lastLine[14]);
            }
            if (lastLine.find_last_of(';') == 14)
            {
                value_l.push_back(lastLine[13]);
            }
        }
        else
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

        break;
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

        break;
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
