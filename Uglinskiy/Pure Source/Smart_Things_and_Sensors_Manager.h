#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <map> 
#include <sstream>




class SmartHouseManager
{
    //string data_from_file = "\0";
public:
    class ISensors
    {
        virtual string current_data_to_string() = 0;
    };

    class LightSensors : public ISensors
    {
        
    public:
        map<string, float> light_sensors;
        LightSensors()
        {
            light_sensors.insert(make_pair("li_sensor_BATH", 0));
            //---------------//
            light_sensors.insert(make_pair("li_sensor_BED", 0));
            //---------------//
            light_sensors.insert(make_pair("li_sensor_L", 0));
            //--------------//
            light_sensors.insert(make_pair("li_sensor_K", 0));

        }

        string current_data_to_string()
        {
            string tmp_string = "\0";
            map<string, float> ::iterator it;
            it = light_sensors.begin();
            while (it != light_sensors.end())
            {
                tmp_string += it->first + "=" + to_string(it->second) + ';';
                it++;
            }
            return tmp_string;
        }


    };

    class TemperatureSensors : public ISensors
    {

    public:
        map<string, int> temperature_sensors;


        TemperatureSensors()
        {
            temperature_sensors.insert(make_pair("tp_sensor_BATH", 0));
            temperature_sensors.insert(make_pair("tp_sensor_BED", 0));
            temperature_sensors.insert(make_pair("tp_sensor_K", 0));
            temperature_sensors.insert(make_pair("tp_sensor_L", 0));

        }
        string current_data_to_string()
        {
            string tmp_string = "\0";
            map<string, int> ::iterator it;
            it = temperature_sensors.begin();
            while (it != temperature_sensors.end())
            {
                tmp_string += it->first + "=" + to_string(it->second) + ';';
                it++;
            }
            return tmp_string;
        }

    };

    class HumiditySensors : public ISensors
    {

    public:
        map<string, int> humidity_sensors;
        map<string, int> ::iterator it;

        HumiditySensors()
        {
            humidity_sensors.insert(make_pair("hm_sensor_BATH", 0));
            humidity_sensors.insert(make_pair("hm_sensor_BED", 0));
            humidity_sensors.insert(make_pair("hm_sensor_K", 0));
            humidity_sensors.insert(make_pair("hm_sensor_L", 0));

        }
        string current_data_to_string()
        {
            string tmp_string = "\0";
            map<string, int> ::iterator it;
            it = humidity_sensors.begin();
            while (it != humidity_sensors.end())
            {
                tmp_string += it->first + "=" + to_string(it->second) + ';';
                it++;
            }
            return tmp_string;
        }
   
    };

    LightSensors LS;
    TemperatureSensors TS;
    HumiditySensors HS;




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
//----------------------///
    //Интерфейс умных вещей
    class ISmartItem
    {
    public:  
        virtual string set_string() = 0;
    };

    //Класс умный свет
    class SmartLight :public ISmartItem
    {      
    public:      
        string set_string()
        {
            return "\0";
        }


        //void set_parametrs(string which_one, string what, int value)
        //{
        //    if (which_one[0]=='l')
        //    {
        //        SL.smart_lamp_char[which_one][what] = value;
        //    }
        //    else if(which_one[0] == 'j')
        //    {
        //        //----
        //    }
        //}

        //int get_parametrs(string which_one, string what)
        //{
        //    if (which_one[0] == 'l')
        //    {
        //       return SL.smart_lamp_char[which_one][what];
        //    }
        //    else if (which_one[0] == 'j')
        //    {
        //        //----
        //    }
        //}

     

        
    };

    //Класс умная лампочка
    class SmartLamp : public SmartLight
    {
    public:
        float max_value = 12, min_value = 0;

        map<string, int> RGBB;
        map<string, map<string, int>> smart_lamp_char;
        SmartLamp()
        {
            RGBB.insert(make_pair("R", 0));
            RGBB.insert(make_pair("G", 0));
            RGBB.insert(make_pair("B", 0));
            RGBB.insert(make_pair("BR", 5));

            smart_lamp_char.insert(make_pair("lamp_1", RGBB));
            smart_lamp_char.insert(make_pair("lamp_2", RGBB));

        }

    public:
        string set_string()
        {
            string return_string = "\0";

            map<string, map<string, int>> ::iterator it;
            it = smart_lamp_char.begin();

            map<string, int> ::iterator it2;
            it2 = it->second.begin();

            return_string = return_string + '\n' + it->first + '\n';
            while (it2 != it->second.end())
            {
                return_string = return_string + it2->first + "=" + to_string(it2->second) + ' ';
                it2++;
            }
            return return_string;
        }
    };




    class SmartJalousie :public SmartLight
    {
    public:
        float max_value = 12, min_value = 0;

        map<string, int> DEG;
        map<string, map<string, int>> smart_jalousie_char;
        SmartJalousie()
        {
            DEG.insert(make_pair("DEG", 0));    

            smart_jalousie_char.insert(make_pair("jalousie_1", DEG));
            smart_jalousie_char.insert(make_pair("jalousie_2", DEG));

        }

    public:
        string set_string()
        {
            string return_string = "\0";

            map<string, map<string, int>> ::iterator it;
            it = smart_jalousie_char.begin();

            map<string, int> ::iterator it2;
            it2 = it->second.begin();

            return_string = return_string + '\n' + it->first + '\n';
            while (it2 != it->second.end())
            {
                return_string = return_string + it2->first + "=" + to_string(it2->second) + ' ';
                it2++;
            }
            return return_string;
        }

    };

    SmartLamp SL;
    SmartJalousie SJ;
       
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
        string data_from_file = get_string();      
        while (i < data_from_file.size())
        {
            while ((data_from_file[i] != ';'))
            {
                if ((data_from_file[i] == 'l') && (data_from_file[i + 14] == 's'))
                {
                    i += 14 + 2;
                    SL.smart_lamp_char["lamp_1"]["BR"] = parse_value(i, data_from_file);
                    i = data_from_file.rfind(to_string(SL.smart_lamp_char["lamp_1"]["BR"]), i);
                    --i;
                }
                else if (data_from_file[i] == 'R')
                {
                    i += 0 + 2;
                    SL.smart_lamp_char["lamp_1"]["R"] = parse_value(i, data_from_file);
                    i = data_from_file.rfind(to_string(SL.smart_lamp_char["lamp_1"]["R"]), i);
                    --i;
                }
                else if (data_from_file[i] == 'G')
                {
                    i += 0 + 2;
                    SL.smart_lamp_char["lamp_1"]["G"] = parse_value(i, data_from_file);
                    i = data_from_file.rfind(to_string(SL.smart_lamp_char["lamp_1"]["G"]), i);
                    --i;
                }
                else if (data_from_file[i] == 'B')
                {
                    i += 0 + 2;
                    SL.smart_lamp_char["lamp_1"]["B"] = parse_value(i, data_from_file);
                    i = data_from_file.rfind(to_string(SL.smart_lamp_char["lamp_1"]["B"]), i);
                    --i;
                }
                else if ((data_from_file[i] == 'j') && (data_from_file[i+14] == 'e'))
                {
                    i += 15 + 2;
                  SJ.smart_jalousie_char["jalousie_1"]["DEG"] = parse_value(i, data_from_file);
                    i = data_from_file.rfind(to_string(SJ.smart_jalousie_char["jalousie_1"]["DEG"]), i);
                    --i;
                }

                ++i;
            }
            ++i;
        }
    }


    //Обсчёт значений датчиков в зависимости от работы умных вещей
    void set_sensors_data()
    {
        LS.light_sensors["li_sensor_L"] =SL.smart_lamp_char["lamp_1"]["BR"]+0.8*SJ.smart_jalousie_char["jalousie_1"]["DEG"];

    }


    //Запись данных с умных вещей в файл
    void write_smart_things_data_in_file()
    {
        time_t now = time(NULL);

        ofstream in_file("Total_sensors_data.txt");
        if (in_file.is_open())
        {

            in_file << asctime(localtime(&now));
            cout << SL.set_string();
            in_file <<  SL.set_string()<< endl;

        }
        in_file.close();
    }
    



    void one_cycle()
    {
        parse_string();
        write_smart_things_data_in_file();
        set_sensors_data();
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