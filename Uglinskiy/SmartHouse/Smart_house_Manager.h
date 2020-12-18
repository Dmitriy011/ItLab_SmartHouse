#pragma once

#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <map>
#include <sstream>

using namespace std;

//интерфейс датчики
class ISensors
{
    virtual string get_string() = 0;
    virtual void set_parameter(string what, int value) = 0;
    virtual float get_parameter(string what) = 0;
};

//класс датчики
class Sensors : public ISensors
{
protected:
    map<string, int> sensors;

public:
    string get_string() override
    {
        string tmp_string = "\0";
        map<string, int>::iterator it;
        it = sensors.begin();
        while (it != sensors.end())
        {
            tmp_string += it->first + "=" + to_string(it->second) + ';';
            it++;
        }
        return tmp_string;
    }
    void set_parameter(string what, int value) override
    {
        sensors[what] = value;
    }

    float get_parameter(string what) override
    {
        return sensors[what];
    }
};

//класс датчики света
class LightSensors : public Sensors
{
public:
    LightSensors()
    {
        sensors.insert(make_pair("li_sensor_BATH", 0));
        sensors.insert(make_pair("li_sensor_BED", 0));
        sensors.insert(make_pair("li_sensor_L", 0));
        sensors.insert(make_pair("li_sensor_K", 0));
    }
};

//класс датчики температуры
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

//класс датчики влажности
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

//интерфейс умный предмет
class ISmartItem
{
public:
    virtual void set_parameter(string, string, int) = 0;
    virtual int get_parameter(string, string) = 0;
    virtual string get_string() = 0;
};

//Класс умный свет
class SmartLight : public ISmartItem
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

        map<string, map<string, int>>::iterator it;
        it = smart_thing_char.begin();

        map<string, int>::iterator it2;
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
private:
    map<string, int> RGBB;

public:
    SmartLamp()
    {
        RGBB.insert(make_pair("R", 0));
        RGBB.insert(make_pair("G", 0));
        RGBB.insert(make_pair("B", 0));
        RGBB.insert(make_pair("BR", 5));

        smart_thing_char.insert(make_pair("lamp_1", RGBB));
        smart_thing_char.insert(make_pair("lamp_2", RGBB));
    }
};

//класс умное жалюзи
class SmartJalousie : public SmartLight
{
private:
    map<string, int> DEG;

public:
    SmartJalousie()
    {
        DEG.insert(make_pair("DEG", 0));

        smart_thing_char.insert(make_pair("jalousie_1", DEG));
        smart_thing_char.insert(make_pair("jalousie_2", DEG));
    }

public:
};

class IServerInfoWorker
{
    virtual string read_data() = 0;
    virtual void save_data(string string_to_file) = 0;
};

class FileInfoWorker : public IServerInfoWorker
{
public:
    string read_data() override
    {
        ifstream in("smart_lamp.txt", ios::in); // окрываем файл для чтения

        std::stringstream sstr;
        sstr << in.rdbuf();
        return sstr.str();
    }
    void save_data(string string_to_file) override
    {
        time_t now = time(NULL);

        ofstream in_file("Total_sensors_data.txt");
        if (in_file.is_open())
        {

            in_file << asctime(localtime(&now));
            cout << asctime(localtime(&now));
            in_file << string_to_file << endl;

            cout << string_to_file << endl;
        }
        in_file.close();
    }
};

//Класс Менеджер
class SmartHouseManager
{
private:
    LightSensors LS;
    TemperatureSensors TS;
    HumiditySensors HS;

    SmartLamp SL;
    SmartJalousie SJ;

    FileInfoWorker FW;

public:
    /*  string convert_data_from_file_to_string(std::ifstream& in)
    {
        std::stringstream sstr;
        sstr << in.rdbuf();
        return sstr.str();
    }*/

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
        string data_from_file = FW.read_data();
        while (i < data_from_file.size())
        {
            if ((data_from_file[i] == 'l') && (data_from_file[i + 1] == 'a'))
            {
                i += 5;
                if ((data_from_file[i] == '1'))
                {
                    i += 2;
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
                i += 4;
                if ((data_from_file[i] == '1'))
                {
                    i += 2;
                    if (data_from_file[i] == 'D')
                    {
                        i += 2 + 2;
                        SJ.set_parameter("jalousie_1", "DEG", parse_value(i, data_from_file));
                        i = data_from_file.find(';', i - 1);
                    }
                }
            }
            ++i;
        }
    }

    //Обсчёт значений датчиков в зависимости от работы умных вещей
    void set_sensors_data()
    {
        float tmp = 0;
        tmp = SL.get_parameter("lamp_1", "BR") + 0.05 * SJ.get_parameter("jalousie_1", "DEG");
        LS.set_parameter("li_sensor_L", tmp);
    }

    //Запись данных с умных вещей в файл
    //void write_smart_things_data_in_file()
    //{
    //    time_t now = time(NULL);

    //    ofstream in_file("Total_sensors_data.txt");
    //    if (in_file.is_open())
    //    {

    //        in_file << asctime(localtime(&now));
    //        cout << asctime(localtime(&now)) ;
    //        in_file << SL.get_string() << endl;
    //        in_file << SJ.get_string() << endl;
    //        cout << SL.get_string() << "\n" << SJ.get_string() << endl;
    //    }
    //    in_file.close();
    //}

    /*   void write_sensors_data_in_file()
    {
        time_t now = time(NULL);

        ofstream in_file("Total_sensors_data.txt", std::ios_base::app);
        if (in_file.is_open())
        {
            in_file << LS.get_string() << endl;
            cout <<"\n" <<LS.get_string();

        }
        in_file.close();
    }*/

    string collect_all_data()
    {
        string all_data = "\0";
        all_data += SL.get_string();
        all_data += SJ.get_string();
        all_data += LS.get_string();

        return all_data;
    }

    void one_cycle()
    {
        parse_string();
        set_sensors_data();
        FW.save_data(collect_all_data());
    }
};
