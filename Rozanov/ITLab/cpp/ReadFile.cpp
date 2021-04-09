#include "ReadFile.h"

void ReadFile::read_txt(Shader& shader, Lamp& lamp, Jalousie& jalousie)
{
    int changed_number = 0;
    int changed_value = 0;

    string filename = "..\\Uglinskiy\\Smart_House\\Smart_House\\smart_lamp.txt";
    //string filename = "D:\\to_add\\Rozanov\\MyInfo\\myInfo.txt";
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

        if (lastLine.find_last_of(';') == 16)
        {
            tmp_changed_value.push_back(lastLine[15]);
        }
        if (lastLine.find_last_of(';') == 17)
        {
            tmp_changed_value.push_back(lastLine[15]);
            tmp_changed_value.push_back(lastLine[16]);
        }

        changed_number = stoi(tmp_changed_number);
        changed_value = stoi(tmp_changed_value);

        jalousie.init_mode_jalousie(changed_number, changed_value);

        break;
    }
    }
}
