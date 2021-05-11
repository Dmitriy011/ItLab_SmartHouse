#include "ReadFile.h"

void ReadFile::read_txt(Shader& shader, Lamp& lamp, Jalousie& jalousie)
{
    int changed_number = 0;
    int changed_value = 0;

    //string filename = "..\\..\\Uglinskiy\\Smart_House\\Smart_House\\smart_lamp.txt";
    string filename = "D:\\LEBEDEV\\to_git\\ItLab_SmartHouse\\Rozanov\\MyInfo\\smart_lamp.txt";
    string tmp_changed_number = "";
    string tmp_changed_value = "";
   
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
        if (lastLine[7] == '_')
        {
            tmp_changed_number.push_back(lastLine[5]);
            tmp_changed_number.push_back(lastLine[6]);

            if (lastLine.find_last_of(';') == 16)
            {
                tmp_changed_value.push_back(lastLine[14]);
                tmp_changed_value.push_back(lastLine[15]);
            }
            if (lastLine.find_last_of(';') == 15)
            {
                tmp_changed_value.push_back(lastLine[14]);
            }
        }
        else
        {
            tmp_changed_number.push_back(lastLine[5]);

            if (lastLine.find_last_of(';') == 15)
            {
                tmp_changed_value.push_back(lastLine[13]);
                tmp_changed_value.push_back(lastLine[14]);
            }
            if (lastLine.find_last_of(';') == 14)
            {
                tmp_changed_value.push_back(lastLine[13]);
            }
        }

        changed_number = stoi(tmp_changed_number);
        changed_value = stoi(tmp_changed_value);

        lamp.change_brightness_light(shader, changed_value, changed_number);

        break;
    }
    case 'j':
    {

        tmp_changed_number.push_back(lastLine[9]);

        if (lastLine.find_last_of(';') == 19)
        {
            tmp_changed_value.push_back(lastLine[18]);
        }
        if (lastLine.find_last_of(';') == 20)
        {
            tmp_changed_value.push_back(lastLine[18]);
            tmp_changed_value.push_back(lastLine[19]);
        }

        changed_number = stoi(tmp_changed_number);
        changed_value = stoi(tmp_changed_value);

        jalousie.init_mode_jalousie(changed_number, changed_value);

        break;
    }
    }
}

void ReadFile::read_txt2(Shader& shader, Lamp& lamp, Jalousie& jalousie)
{
    string str;
    int count = 0;
   // ifstream f("D:\\LEBEDEV\\to_git\\ItLab_SmartHouse\\Rozanov\\MyInfo\\test.txt");
    ifstream f("..\\cacher\\cache.txt");

    while (1)
    {
        ++count;
        getline(f, str);

        if (count < 13)
        {
            if (str != "" && (str.length() == 1 || str.length() == 2) && lamp.modes_lights[count - 1] != stoi(str))
            {
                lamp.change_brightness_light(shader, stoi(str), count);
            }
        }

        if (count >= 13 && count < 17)
        {
            if (str != "" && (str.length() == 1 || str.length() == 2) && jalousie.mode_j[3] != stoi(str) )
            {
                jalousie.init_mode_jalousie(count - 12, stoi(str));
            }
        }

        if (count == 17)
        {
            break;
        }
    }
}
