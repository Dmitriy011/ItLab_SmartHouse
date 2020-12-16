#pragma once

#pragma warning(disable:4996)

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <map> 
#include <sstream>

using namespace std;


class Sensors
{
protected:
    map<string, float> sensors;
public:
    virtual string current_data_to_string()
    {
        string tmp_string = "\0";
        map<string, float> ::iterator it;
        it = sensors.begin();
        while (it != sensors.end())
        {
            tmp_string += it->first + "=" + to_string(it->second) + ';';
            it++;
        }
        return tmp_string;
    }
};

class LightSensors : public Sensors
{
    map<string, float> light_sensors;
public:
   
    LightSensors()
    {
        sensors.insert(make_pair("li_sensor_BATH", 0));
        sensors.insert(make_pair("li_sensor_BED", 0));
        sensors.insert(make_pair("li_sensor_L", 0));
        sensors.insert(make_pair("li_sensor_K", 0));

    }
};

class TemperatureSensors : public Sensors
{   
public:
 
    TemperatureSensors()
    {
        sensors.insert(make_pair("tp_sensor_BATH", 0));
        sensors.insert(make_pair("tp_sensor_BED", 0));
        sensors.insert(make_pair("tp_sensor_K", 0));
        sensors.insert(make_pair("tp_sensor_L", 0));

    }

};

class HumiditySensors : public Sensors
{    
public:   
    HumiditySensors()
    {
        sensors.insert(make_pair("hm_sensor_BATH", 0));
        sensors.insert(make_pair("hm_sensor_BED", 0));
        sensors.insert(make_pair("hm_sensor_K", 0));
        sensors.insert(make_pair("hm_sensor_L", 0));

    }
};




class ISmartItem
{
public:
    virtual void   set_parameter(string , string ,int ) = 0;
    virtual int    get_parameter(string, string) = 0;
    virtual string get_string() = 0;
};

//Класс умный свет
class SmartLight :public ISmartItem
{
protected:
    map<string, map<string, int>> smart_thing_char;
public:
    
    void set_parameter(string which_one, string what, int value) override
    {     
            smart_thing_char[which_one][what] = value;            
    }

    int get_parameter(string which_one, string what) override
    {       
           return smart_thing_char[which_one][what];            
    }
    string get_string() override
    {
        string return_string = "\0";

        map<string, map<string, int>> ::iterator it;
        it = smart_thing_char.begin();

        map<string, int> ::iterator it2;       
        while (it != smart_thing_char.end())
        {
            it2 = it->second.begin();
            return_string = return_string + '\n' + it->first + '\n';
            while (it2 != it->second.end())
            {
                return_string = return_string + it2->first + "=" + to_string(it2->second) + ' ';
                it2++;
            }
            it++;
        }
        return return_string;
    }



};

//Класс умная лампочка
class SmartLamp : public SmartLight
{
   
   // map<string, map<string, int>> smart_thing_char;
public: 
    map<string, int> RGBB;
    SmartLamp()
    {
        RGBB.insert(make_pair("R", 0));
        RGBB.insert(make_pair("G", 0));
        RGBB.insert(make_pair("B", 0));
        RGBB.insert(make_pair("BR", 5));

    /*  smart_thing_char["lamp_1"] = RGBB;
        smart_thing_char["lamp_2"] = RGBB;*/
        smart_thing_char.insert(make_pair("lamp_1", RGBB));
        smart_thing_char.insert(make_pair("lamp_2", RGBB));
        
    }   
};




class SmartJalousie :public SmartLight
{
    map<string, int> DEG;
   // map<string, map<string, int>> smart_thing_char;
public: 
    SmartJalousie()
    {
        DEG.insert(make_pair("DEG", 0));

        smart_thing_char.insert(make_pair("jalousie_1", DEG));
        smart_thing_char.insert(make_pair("jalousie_2", DEG));

    }

public:

};




//Класс Менеджер
class SmartHouseManager
{
    LightSensors LS;
    TemperatureSensors TS;
    HumiditySensors HS;

    SmartLamp SL;
    SmartJalousie SJ;
    
    
public:
    //-----------------/func

    void write_sensors_data_in_file()
    {
        //  time_t now = time(NULL);

        ofstream in_file("Total_sensors_data.txt", ios::app);
        if (in_file.is_open())
        {
            cout << LS.current_data_to_string();
            // in_file << asctime(localtime(&now));
            in_file << LS.current_data_to_string() << endl;
            /* in_file << TS.total_current_data << endl;
             in_file << HS.total_current_data << endl;*/
        }
        in_file.close();
    }
    //---------------------//

    string convert_data_from_file_to_string(std::ifstream& in)
    {
        std::stringstream sstr;
        sstr << in.rdbuf();
        return sstr.str();
    }

    string get_string()
    {
        ifstream in("smart_lamp.txt", ios::in); // окрываем файл для чтения

       // cout << "Data from file:\n" << convert_data_from_file_to_string(in) << endl;
        return convert_data_from_file_to_string(in);
    }
     
    //Парсер
    int parse_value(int start_index, string value_from_datafile)
    {
        int i = start_index;
        string tmp_value = "\0";

        while ((value_from_datafile[i] >= 48) && (value_from_datafile[i] <= 57))
        {
            tmp_value = tmp_value + to_string(value_from_datafile[i] - 48);
            ++i;
        }

        return stoi(tmp_value);
    }

    void parse_string()
    {
        int i = 0;
        int tmp = 0;
        string data_from_file = get_string();       
        while (i < data_from_file.size())
        {        
                if ((data_from_file[i] == 'l') && (data_from_file[i + 1] == 'a'))
                {
                    i += 5;
                    if ((data_from_file[i] == '1'))
                    {
                        i+=2;
                        if ((data_from_file[i] == 'B') && (data_from_file[i + 1] == 'R'))
                        {
                            i += 1 + 2;
                                SL.set_parameter("lamp_1", "BR", parse_value(i, data_from_file));                                                        
                                i = data_from_file.find(';', i - 1);
                        }
                        else if (data_from_file[i] == 'R')
                        {
                            i += 0 + 2;
                            SL.set_parameter("lamp_1", "R ", parse_value(i, data_from_file));
                            i = data_from_file.find(';', i - 1);
                        }
                        else if (data_from_file[i] == 'G')
                        {
                            i += 0 + 2;
                            SL.set_parameter("lamp_1", "G ", parse_value(i, data_from_file));
                            i = data_from_file.find(';', i - 1);
                        }
                        else if (data_from_file[i] == 'B')
                        {
                            i += 0 + 2;
                            SL.set_parameter("lamp_1", "B", parse_value(i, data_from_file));
                            i = data_from_file.find(';', i - 1);
                        }
                    }
                    if ((data_from_file[i] == '2'))
                    {
                        i += 2;
                        if ((data_from_file[i] == 'B') && (data_from_file[i + 1] == 'R'))
                        {
                            i += 1 + 2;
                            SL.set_parameter("lamp_2", "BR", parse_value(i, data_from_file));
                            i = data_from_file.find(';', i - 1);
                        }
                        else if (data_from_file[i] == 'R')
                        {
                            i += 0 + 2;
                            SL.set_parameter("lamp_2", "R", parse_value(i, data_from_file));
                            i = data_from_file.find(';', i - 1);
                        }
                        else if (data_from_file[i] == 'G')
                        {
                            i += 0 + 2;
                            SL.set_parameter("lamp_2", "G", parse_value(i, data_from_file));
                            i = data_from_file.find(';', i - 1);
                        }
                        else if (data_from_file[i] == 'B')
                        {
                            i += 0 + 2;
                            SL.set_parameter("lamp_2", "B", parse_value(i, data_from_file));
                            i = data_from_file.find(';', i - 1);
                        }
                    }
                }
                else if ((data_from_file[i] == 'j') && (data_from_file[i + 1] == 'l'))
                {
                    i +=4;
                    if ((data_from_file[i] == '1')) 
                    {
                        if (data_from_file[i] == 'D')
                        {
                            i += 0 + 2;
                            SL.set_parameter("jalousie_", "DEG", parse_value(i, data_from_file));
                            i = data_from_file.find(';', i - 1);
                        }
                    }
                }
                ++i;                  
        }
    }


    //Обсчёт значений датчиков в зависимости от работы умных вещей
    /*void set_sensors_data()
    {
      LS. = SL.smart_lamp_char["lamp_1"]["BR"] + 0.8 * SJ.smart_jalousie_char["jalousie_1"]["DEG"];

    }*/
  
    //Запись данных с умных вещей в файл
    void write_smart_things_data_in_file()
    {
        time_t now = time(NULL);

        ofstream in_file("Total_sensors_data.txt");
        if (in_file.is_open())
        {

            in_file << asctime(localtime(&now));
            cout << asctime(localtime(&now)) <<SL.get_string();
            in_file << SL.get_string() << endl;

        }
        in_file.close();
    }

    void one_cycle()
    {
        parse_string();
        write_smart_things_data_in_file();
      //  set_sensors_data();
        write_sensors_data_in_file();       
    }
};



//
//int parse_value(int start_index, string value_from_datafile)
//{
//    int i = start_index;
//    string tmp_value = "\0";
//
//    while ((value_from_datafile[i] >= 48) && (value_from_datafile[i] <= 57))
//    {
//        tmp_value = tmp_value + to_string(value_from_datafile[i] - 48);
//        ++i;
//    }
//
//    return stoi(tmp_value);
//}

//void parse_string(string data_from_file, SmartLamp& SL)
//{
//
//    int i = 0;
//    int value_from_file = 0;
//    while (i < data_from_file.size())
//    {
//        while ((data_from_file[i] != ';'))
//        {
//            if ((data_from_file[i] == 'l') && (data_from_file[i + 14] == 's'))
//            {
//                i += 14 + 2;
//                SL.smart_lamp_char["lamp_1"]["BR"] = parse_value(i, data_from_file);
//                i = data_from_file.rfind(to_string(SL.smart_lamp_char["lamp_1"]["BR"]), i);
//                --i;
//            }
//            else if (data_from_file[i] == 'R')
//            {
//                i += 0 + 2;
//                SL.smart_lamp_char["lamp_1"]["R"] = parse_value(i, data_from_file);
//                i = data_from_file.rfind(to_string(SL.smart_lamp_char["lamp_1"]["R"]), i);
//                --i;
//            }
//            else if (data_from_file[i] == 'G')
//            {
//                i += 0 + 2;
//                SL.smart_lamp_char["lamp_1"]["G"] = parse_value(i, data_from_file);
//                i = data_from_file.rfind(to_string(SL.smart_lamp_char["lamp_1"]["G"]), i);
//                --i;
//            }
//            else if (data_from_file[i] == 'B')
//            {
//                i += 0 + 2;
//                SL.smart_lamp_char["lamp_1"]["B"] = parse_value(i, data_from_file);
//                i = data_from_file.rfind(to_string(SL.smart_lamp_char["lamp_1"]["B"]), i);
//                --i;
//            }
//
//            ++i;
//        }
//        ++i;
//
//
//    }
//
//
//}