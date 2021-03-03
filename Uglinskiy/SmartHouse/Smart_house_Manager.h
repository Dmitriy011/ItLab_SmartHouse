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
     map<string, int> sensors;//мапа сенсоров
public:

    string get_string() override
    {
        string tmp_string = "\0";//создаём пустую строку
        map<string, int>::iterator it;//создаём итератор

        it = sensors.begin();//устанавливаем итератор в начало

        while (it != sensors.end())//Цикл: пока не достигнем конца мапы
        {
            tmp_string += it->first + "=" + to_string(it->second) + ',';//добавляем к текущей строке: "ключ = значение ключа,"
            ++it;
            if (it == sensors.end())//убираем последнюю ненужную запятую
            {
                tmp_string.erase(tmp_string.size() - 1);//вроде работает,но выглядит не очень 
            }
        }
        return tmp_string;
    }

    void set_parameter(string what, int value) override//устанвливаем значение value  по ключу what
    {
        sensors[what] = value;
    }

    float get_parameter(string what) override//получаем  значение  по ключу what
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
    map<string, int> smart_thing_char;// мапа-характеристики умной вещи

public:
    void set_parameter(string what, int value) override//устанвливаем значение value  по ключу what
    {
        smart_thing_char[what] = value;
    }

    int get_parameter(string what) override//получаем  значение  по ключу what
    {
        return smart_thing_char[what];
    }
    string get_string() override
    {
        string return_string = "\0";//создаём пустую строку

        map<string, int>::iterator it;//создаём итератор 
        it = smart_thing_char.begin();//устанавливаем итератор в начало мапы

        while (it != smart_thing_char.end())//Цикл: пока не достигнем конца мапы
        {              
                return_string +=it->first + "=" + to_string(it->second) + ',';//добавляем к текущей строке: "ключ = значение ключа,"
                ++it; 
                if(it == smart_thing_char.end())//убираем последнюю ненужную запятую
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
    //Чтение данных из файла
    string read_data() override
    {
        ifstream in("smart_lamp.txt", ios::in); // окрываем файл для чтения

        std::stringstream sstr;
        sstr << in.rdbuf();
        return sstr.str();
    }
    //Запись данных в файл
    void save_data(string string_to_file) override
    {
        time_t now = time(NULL);//созда1м переменую времени

        ofstream in_file("Total_sensors_data.txt");
        if (in_file.is_open())
        {

            in_file << asctime(localtime(&now));//Записываем текущее время
            cout << asctime(localtime(&now));
            in_file << string_to_file << endl;//записываем данные из принятой строки в файл

            cout << string_to_file << endl;
        }
        in_file.close();//закрываем файл
    }
};

//Класс Менеджер
class SmartHouseManager
{
private:
    //создаём классы сенсоры
    LightSensors LS;
    TemperatureSensors TS;
    HumiditySensors HS;
   
    //создаём векторы умных вещеё
    vector<SmartLamp> smart_lamps_vec;
    vector<SmartJalousie> smart_jalousie_vec;

    //создаём класс работы с файлами
    ServerInfoFileWorker FW;

   
    //Распарсивание строки цифр в число,например (string)"123"->(int)123
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

    //Ошибка:количество данных принятых с сервера больше чем количество умных вещей
    void exception_out_of_range()
    {
        cout <<"ERROR: the number of smart things received from the server is greater than it really exists : the program is closing"<<"\n";
        exit(1);
    }

public:
    SmartHouseManager(int lenght_lamps = 1, int lenght_jalousie = 1)//конструктор 
    {
        //инициализация количесва умных вещей
        smart_lamps_vec.resize(lenght_lamps);
        smart_jalousie_vec.resize(lenght_jalousie);
             
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
                   
                   if (item_number + 1 > smart_lamps_vec.size())
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
                   
                   if(item_number + 1 > smart_jalousie_vec.size())
                   {
                       exception_out_of_range();
                   }
                  
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
        float E = 0, Ia = 0, S=10;
        float tmp = 0;
        float sun_brightness = 7;
        int tmp2 = 0;
      /*Ia - сила света в направлении от источника на заданную точку рабочей поверхности 
        ( определяют по кривым силы света или по таблицам выбранного типа светильника),
        S-Плоащадь комнаты  */
      
        for (int i = 0; i < smart_lamps_vec.size(); i++)
        {
            Ia += smart_lamps_vec[i].get_parameter("BR");
        }
        Ia = Ia / smart_lamps_vec.size();
        E = (Ia* smart_lamps_vec.size())/S;         
        for (int i = 0; i < smart_jalousie_vec.size(); i++)
        {
            if (smart_jalousie_vec[i].get_parameter("DEG") <= 90)
            {
                tmp2 = smart_jalousie_vec[i].get_parameter("DEG");
            }
            else
            { 
                tmp2 = 90 - ((smart_jalousie_vec[i].get_parameter("DEG")) % 90);
            }
            
            tmp += sun_brightness *((float)tmp2  /  90);
        }
        E += tmp;
        LS.set_parameter("L", E);
    }

    //Собрать все данные в одну строку
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

    //Один цикл программы
    void one_cycle()
    {
        parse_string();
        set_sensors_data();
        FW.save_data(collect_all_data());
    }
};
