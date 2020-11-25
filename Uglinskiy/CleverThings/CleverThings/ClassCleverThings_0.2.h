#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <map> 
#include <sstream>

using namespace std;

enum ON_OFF {OFF=0,ON=1};

///------------Class Sensors--------------
class ISensors
{
    virtual string generate_one_lexeme(int start_index) = 0;
};

class LightSensors : public ISensors
{
    map<string, int> light_sensors;
public:
   
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
  string  generate_one_lexeme(int start_index) override
    {
      string one_lexem = "\0";
      int tmp_propertie = 0;
      map<string, int> ::iterator it;
      it = light_sensors.begin();
      
      advance(it, start_index);
      tmp_propertie = rand() % 481 + 20;
      it->second = tmp_propertie;

      one_lexem = it->first + '=' + to_string(it->second) + ";";
      return one_lexem;
    }

  string generate__light_sensors_data()
  {
      string sensors_data = "\0";
      int total_le = light_sensors.size();

      for (int i = 0; i < total_le; i++)
      {
          if (((i % 6) == 0) && (i != 0))
          {
              sensors_data = sensors_data + "\n";
          }
          sensors_data = sensors_data + generate_one_lexeme(i);
      }
     // cout << sensors_data << endl;
      return sensors_data;
  }

    
};

class TemperatureSensors : public ISensors
{
    map<string, int> temperature_sensors;
public:
    TemperatureSensors()
    {
        temperature_sensors.insert(make_pair("tp_sensor_BATH",0));
        temperature_sensors.insert(make_pair("tp_sensor_BED", 0));
        temperature_sensors.insert(make_pair("tp_sensor_K", 0));
        temperature_sensors.insert(make_pair("tp_sensor_L", 0));
    }
    string  generate_one_lexeme(int start_index) override
    {
        string one_lexem = "\0";
        int tmp_propertie = 0;
        map<string, int> ::iterator it;
        it = temperature_sensors.begin();

        advance(it, start_index);
        tmp_propertie = rand() % 150 - 50;
        it->second = tmp_propertie;

        one_lexem = it->first + '=' + to_string(it->second) + ";";
        return one_lexem;
    }
    string generate__temperature_sensors_data()
    {
        string sensors_data = "\0";
        int total_le = temperature_sensors.size();

        for (int i = 0; i < total_le; i++)
        {
            if (((i % 6) == 0) && (i != 0))
            {
                sensors_data = sensors_data + "\n";
            }
            sensors_data = sensors_data + generate_one_lexeme(i);
        }
        // cout << sensors_data << endl;
        return sensors_data;
    }
};

class HumiditySensors : public ISensors
{
    map<string, int> humidity_sensors;
public:
    HumiditySensors()
    {
        humidity_sensors.insert(make_pair("hm_sensor_BATH", 0));
        humidity_sensors.insert(make_pair("hm_sensor_BED", 0));
        humidity_sensors.insert(make_pair("hm_sensor_K", 0));
        humidity_sensors.insert(make_pair("hm_sensor_L", 0));

    }
    string  generate_one_lexeme(int start_index) override
    {
        string one_lexem = "\0";
        int tmp_propertie = 0;
        map<string, int> ::iterator it;
        it = humidity_sensors.begin();

        advance(it, start_index);
        tmp_propertie = rand() % 101;
        it->second = tmp_propertie;

        one_lexem = it->first + '=' + to_string(it->second) + ";";
        return one_lexem;
    }
    string generate__humidity_sensors_data()
    {
        string sensors_data = "\0";
        int total_le = humidity_sensors.size();

        for (int i = 0; i < total_le; i++)
        {
            if (((i % 6) == 0) && (i != 0))
            {
                sensors_data = sensors_data + "\n";
            }
            sensors_data = sensors_data + generate_one_lexeme(i);
        }
        // cout << sensors_data << endl;
        return sensors_data;
    }

};



void write_sensors_data_in_file(string light_sensors_data, string temperature_sensors_data,string humidity_sensors_data)
{
    time_t now = time(NULL);
  
    ofstream in_file("C:\\Users\\Kek\\Desktop\\Total_sensors_data.txt"/*, ios::app*/);//*
    if (in_file.is_open())
    {
        
        in_file << asctime(localtime(&now));
        in_file << light_sensors_data << endl;
        in_file << temperature_sensors_data << endl;
        in_file << humidity_sensors_data << endl;
    }
    in_file.close();
}




///-----------------Class SmartItem

void parse_line()
{

}


class ISmartItem
{public:
   virtual void initialize_string( ) = 0;
   virtual string set_string() = 0;
};

class SmartLight:public ISmartItem
{
protected:
    
    string data_from_file ="\0";
    map<string, int> characteristics;
    int total_characteristics = 0;
  
    public:
        string get_string(std::ifstream & in) 
        {
            std::stringstream sstr;
            sstr << in.rdbuf();
            return sstr.str();
        }

        void initialize_string() override
        {
            ifstream in("C:\\Users\\Kek\\Desktop\\smart_lamp.txt", ios::in); // окрываем файл для чтения
            data_from_file=get_string(in);
            cout <<"Data from file:\n"<< data_from_file << endl;
        }

    

    string set_string() override
    {
        return "\0";
    }
   /* void parse_string() override
    {
        return ;
    }*/
       void parse_string()
    {
       int i = 0;
        int value_from_file = 0;
        string tmp_value = "\0";
        while (data_from_file[i] != '\0')
        {
            map<string, int> ::iterator it;
            it = characteristics.begin();
            while ((data_from_file[i] != ';'))
            {
                if ((data_from_file[i] == 'p') && (data_from_file[i + 6] == 'i'))
                {

                    i += 6 + 2;
                    while ((data_from_file[i] >= 48) && (data_from_file[i] <= 57))
                    {
                        tmp_value = tmp_value + to_string(data_from_file[i] - 48);
                        cout << tmp_value << endl;
                        ++i;
                    }

                    value_from_file = stoi(tmp_value);
                    characteristics.insert(make_pair("power_of_light", value_from_file));
                    //it = characteristics.find("power_of_light");                  
                    --i;
                    cout << "Value_from_file =" << value_from_file<<endl;
                    value_from_file = 0;
                    tmp_value = "\0";
                }
                ++i;
            }        
            ++i;
           
           
        }      
      
    }


 
    
  
    bool on_off = 0;

    virtual void print_info() = 0; //Вывод текущей информации об объекте
    bool is_on()
    {
        if (on_off == ON)
        {
            cout << "ON" << endl;
            return 1;
        }
        else
        {
            cout << "OFF" << endl;
            return 0;
        }
    }



    /*float get_degree() //Получение значения состояния
    {
        return this->degree;
    };
    void set_degree(float new_degree) //Установка значения состояния
    {
        degree = new_degree;
    };

    void set_on_off(bool temp_on_off) //Вкл/выкл
    {

        on_off = temp_on_off;
    }
    */


};


//Класс умная лампочка
class SmartLamp : public SmartLight
{

public:

    float max_value = 12, min_value = 0;
    map<string, int> RGBB;

    map<string, map<string,int>> smart_lamp_char;
    int power_of_light = 0;
        int red = 0;
        int green = 0;
        int blue = 0;
        SmartLamp()
        {
            RGBB.insert(make_pair("R", 0));
            RGBB.insert(make_pair("G", 0));
            RGBB.insert(make_pair("B", 0));
            RGBB.insert(make_pair("BR", 0));

            smart_lamp_char.insert(make_pair("lamp_1", RGBB));
            smart_lamp_char.insert(make_pair("lamp_2", RGBB));

        }
        
  

public:

    void set_p_of_li()
    {
        map<string, int> ::iterator it;
        it = characteristics.find("power_of_light");
        smart_lamp_char["lamp_1"]["R"] = 256;
       

    }
    void print_info() override
    {
      
      
       cout << "Red: " << smart_lamp_char["lamp_1"]["R"] << " " << endl;
    }
};

//---------------------------------------------------------//

class SmartClimateControl
{
};

class SmartBatteries : public SmartClimateControl
{
};

class SmartWarmFloor : public SmartClimateControl
{
};

class SmartWindow : public SmartClimateControl
{
};

class SmartWindowLeaf : public SmartClimateControl
{
};

class Humidifier : public SmartClimateControl
{
};

class Conditioner : public SmartClimateControl
{
};
//---------------------
class SmartJalousie : public SmartLight, public SmartClimateControl
{
    float max_value = 100, min_value = 0;

};

class SmartCurtains : public SmartLight, public SmartClimateControl
{
};

//----------------------------//
