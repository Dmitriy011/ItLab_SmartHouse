#include "ReadFile.h"

void ReadFile::read_txt(Shader& shader, Lamp& lamp, Jalousie& jalousie)
{
    int changed_number = 0;
    int changed_value = 0;

    string filename = "..\\..\\Uglinskiy\\Smart_House\\Smart_House\\smart_lamp.txt";
    //string filename = "D:\\LEBEDEV\\to_git\\ItLab_SmartHouse\\Rozanov\\MyInfo\\smart_lamp.txt";
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

void ReadFile::read_bd(Shader& shader, Lamp& lamp, Jalousie& jalousie)
{
    size_t power_current_lamp = 0;
    size_t mode_jalousie = 0;

    for (size_t i = 1; i < 4; i++)
    {
        // {"living/lamp/i": "living/lamp/i", "power": 10}
        //power_current_lamp = power;
        if (lamp.modes_lights[i - 1] != power_current_lamp)
        {
            lamp.change_brightness_light(shader, power_current_lamp, i);
        }

        // {"bed/lamp/i": "bed/lamp/i", "power": 10}
        //power_current_lamp = power;
        if (lamp.modes_lights[3 + i - 1] != power_current_lamp)
        {
            lamp.change_brightness_light(shader, power_current_lamp, 3 + i);
        }

        // {"bath/lamp/i": "bath/lamp/i", "power": 10}
        //power_current_lamp = power;
        if (lamp.modes_lights[6 + i - 1] != power_current_lamp)
        {
            lamp.change_brightness_light(shader, power_current_lamp, 6 + i);
        }

        // {"living/lamp/i": "living/lamp/1", "power": 10}
        //power_current_lamp = power;
        if (lamp.modes_lights[9 + i - 1] != power_current_lamp)
        {
            lamp.change_brightness_light(shader, power_current_lamp, 9 + i);
        }
    }

    //{"living/jalousie": "bed/jalousie, "mode"}
    //mode_jalousie = mode;
    if (jalousie.mode_j[0] != mode_jalousie)
    {
        jalousie.init_mode_jalousie(1, mode_jalousie);
    }

    //{"bed/jalousie": "bed/jalousie", "mode"}
    //mode_jalousie = mode;
    if (jalousie.mode_j[1] != mode_jalousie)
    {
        jalousie.init_mode_jalousie(2, mode_jalousie);
    }

    //{"kitchen/jalousie": "kitchen/jalousie", "mode"}
    //mode_jalousie = mode;
    if (jalousie.mode_j[2] != mode_jalousie)
    {
        jalousie.init_mode_jalousie(3, mode_jalousie);
    }

    //{"bath/jalousie": "bath/jalousie", "mode"}
    //mode_jalousie = mode;
    if (jalousie.mode_j[3] != mode_jalousie)
    {
        jalousie.init_mode_jalousie(4, mode_jalousie);
    }

}
