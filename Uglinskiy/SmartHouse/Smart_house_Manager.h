#pragma once

#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

//интерфейс датчики
class ISensors
{
    virtual string get_string() = 0;//составить и получить строку с текущими значениями датчиков
    virtual void set_parameter(string what, int value) = 0;//установить значение поля по ключу
    virtual float get_parameter(string what) = 0;//получить значение поля по ключу
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
            tmp_string += it->first + "=" + to_string(it->second) + ',';
            ++it;
            if (it == sensors.end())
            {
                tmp_string.erase(tmp_string.size() - 1);//вроде работает,но выглядит не очень 
            }
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
        sensors.insert(make_pair("BATH", 0));
        sensors.insert(make_pair("BED", 0));
        sensors.insert(make_pair("L", 0));
        sensors.insert(make_pair("K", 0));
        sensors.insert(make_pair("OUT", 0));
    }
};

//класс датчики температуры
class TemperatureSensors : public Sensors
{
public:

    TemperatureSensors()
    {
        sensors.insert(make_pair("BATH", 0));
        sensors.insert(make_pair("BED", 0));
        sensors.insert(make_pair("K", 0));
        sensors.insert(make_pair("L", 0));
    }
};

//класс датчики влажности
class HumiditySensors : public Sensors
{
public:

    HumiditySensors()
    {
        sensors.insert(make_pair("BATH", 0));
        sensors.insert(make_pair("BED", 0));
        sensors.insert(make_pair("K", 0));
        sensors.insert(make_pair("L", 0));
    }
};


//интерфейс умный предмет
class ISmartItem
{
public:
    virtual void set_parameter(string, int) = 0;//установить значение поля  по ключу
    virtual int get_parameter(string) = 0;//получить значения поля по ключу
    virtual string get_string() = 0;//составить и вернуть строку с текущими значениями полей
};

//Класс умный свет
class SmartLight : public ISmartItem
{
protected:
    map<string, int> smart_thing_char;

public:
    void set_parameter(string what, int value) override
    {
        smart_thing_char[what] = value;
    }

    int get_parameter(string what) override
    {
        return smart_thing_char[what];
    }
    string get_string() override
    {
        string return_string = "\0";

        map<string, int>::iterator it;
        it = smart_thing_char.begin();

        while (it != smart_thing_char.end())
        {              
                return_string +=it->first + "=" + to_string(it->second) + ',';
                ++it; 
                if(it == smart_thing_char.end())
                {
                    return_string.erase(return_string.size() - 1);//вроде работает,но выглядит не очень 
                }
        }
        return return_string;
    }
};

//Класс умная лампочка
class SmartLamp : public SmartLight
{
private:
 
public:
    SmartLamp()
    {
        smart_thing_char.insert(make_pair("R", 0));
        smart_thing_char.insert(make_pair("G", 0));
        smart_thing_char.insert(make_pair("B", 0));
        smart_thing_char.insert(make_pair("BR", 5));    
    }
};

//класс умное жалюзи
class SmartJalousie : public SmartLight
{
private:

public:
    SmartJalousie()
    {
        smart_thing_char.insert(make_pair("DEG", 0));
    }
};



//

class IServerInfoWorker
{
    virtual string read_data() = 0;
    virtual void save_data(string string_to_file) = 0;
};

class ServerInfoFileWorker : public IServerInfoWorker
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
   
    vector<SmartLamp> smart_lamps_vec;
    vector<SmartJalousie> smart_jalousie_vec;

    ServerInfoFileWorker FW;

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

    void exception_out_of_range()
    {
        cout <<"ERROR: the number of smart things received from the server is greater than it really exists : the program is closing"<<"\n";
        exit(1);
    }

public:
    SmartHouseManager(int lenght_lamps = 1, int lenght_jalousie = 1)
    {
        smart_lamps_vec.resize(lenght_lamps);
        smart_jalousie_vec.resize(lenght_jalousie);
       
    }
 
    void make_vector(int size_SL,int size_SJ)
    {
        cout << smart_lamps_vec.size();

       /* smart_lamps.resize(size_SL);
        smart_jalousie.resize(size_SJ);*/
    }

  /*  void foo()
    {
        smart_lamps[0].set_parameter("R", 255);
        cout << smart_lamps[0].get_parameter("R");
    }*/

    //Парсер
    void parse_string()
    {
        int i = 0;
        int item_number = 0;
        string data_from_file = FW.read_data();
        while (i < data_from_file.size())
        {
            if ((data_from_file[i] == 'l') && (data_from_file[i + 1] == 'a'))
            {              
                   i += 5;
                   item_number = parse_value(i, data_from_file)-1;
                   if ((item_number + 1 > smart_lamps_vec.size()) || (item_number > smart_jalousie_vec.size()))
                   {                    
                       exception_out_of_range();
                   }

                   i = data_from_file.find(':', i) + 1;
                    while (data_from_file[i] != ';')
                    {
                        if ((data_from_file[i] == 'B') && (data_from_file[i + 1] == 'R'))
                        {
                            i += 1 + 2;
                            smart_lamps_vec[item_number].set_parameter("BR", parse_value(i, data_from_file));
                            i = data_from_file.find(',', i - 1)+1;
                        }
                        if (data_from_file[i] == 'R')
                        {
                            i += 0 + 2;
                            smart_lamps_vec[item_number].set_parameter("R", parse_value(i, data_from_file));
                            i = data_from_file.find(',', i - 1) + 1;
                        }
                        if (data_from_file[i] == 'G')
                        {
                            i += 0 + 2;
                            smart_lamps_vec[item_number].set_parameter("G", parse_value(i, data_from_file));
                            i = data_from_file.find(',', i - 1) + 1;
                        }
                        if ((data_from_file[i] == 'B') && (data_from_file[i + 1] != 'R'))
                        {
                            i += 0 + 2;
                            smart_lamps_vec[item_number].set_parameter("B", parse_value(i, data_from_file));
                            i = data_from_file.find(';', i - 1);
                        }
                        else
                        { 
                            i++; 
                        }
                    
                    }
            }
            else if ((data_from_file[i] == 'j') && (data_from_file[i + 1] == 'a'))
            {
                   i += 9;
                   item_number = parse_value(i, data_from_file)-1;
                  
                   i = data_from_file.find(':', i) + 1;
                    while (data_from_file[i] != ';') 
                    {
                      if (data_from_file[i] == 'D')
                      {
                        i += 2 + 2;
                        smart_jalousie_vec[item_number].set_parameter("DEG", parse_value(i, data_from_file));
                        i = data_from_file.find(';', i - 1);
                      }
                      else
                      {
                        i++;
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
        tmp = smart_lamps_vec[0].get_parameter("BR") + 0.05 * smart_jalousie_vec[0].get_parameter("DEG");
        LS.set_parameter("L", tmp);
    }

    //Запись данных с умных вещей в файл
  
  /*  void write_smart_things_data_in_file()
    {
        time_t now = time(NULL);

        ofstream in_file("Total_sensors_data.txt");
        if (in_file.is_open())
        {
            in_file << asctime(localtime(&now));
            cout << asctime(localtime(&now)) ;
            for (int i = 0; i < smart_lamps_vec.size(); i++)
            {
                in_file << "lamp_" << i << ":" << smart_lamps_vec[i].get_string() << endl;
            }
            for (int i = 0; i < smart_jalousie_vec.size(); i++)
            {
                in_file << "jalousie_" << i << ":"<<smart_jalousie_vec[i].get_string() << endl;
            }        
        }
        in_file.close();
    }*/

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
        for (int i = 0; i < smart_lamps_vec.size(); i++)
        {
            all_data += "lamp_"+to_string(i+1)+":"+smart_lamps_vec[i].get_string()+";\n";
        }     
        for (int i = 0; i < smart_jalousie_vec.size(); i++)
        {
            all_data += "jalousie_"+ to_string(i+1)+ ":" +smart_jalousie_vec[i].get_string() + ";\n";
        }
        all_data +="li_sensor:" + LS.get_string()+";\n"+ "tm_sensors:"+TS.get_string()+ ";\n"+"hm_sensors"+ HS.get_string()+ ";\n";

        return all_data;
    }

    void one_cycle()
    {
        parse_string();
        set_sensors_data();
        FW.save_data(collect_all_data());
    }
};
