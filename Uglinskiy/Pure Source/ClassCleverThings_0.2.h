#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <map> 

using namespace std;

enum ON_OFF {OFF=0,ON=1};

///------------Class Sensors--------------
class ISensors
{
    virtual string generate_one_lexeme(/*int tmp_sensor*/) = 0;
    virtual void write_lexeme_in_file() = 0;
};


class LightSensors : ISensors
{
    string one_lexem = "\0";
    int tmp_propertie = 0;

public:
    LightSensors()
    {
        tmp_propertie = rand() % 481 + 20;
    }
  string  generate_one_lexeme(/*int tmp_sensor*/) override
    {
      one_lexem = "p_of_li";
      one_lexem = one_lexem+"="; /*+ to_string(tmp_sensor);*/
      //one_lexem = one_lexem + "=";
      tmp_propertie = rand() % 481 + 20;
      one_lexem = one_lexem + to_string(tmp_propertie) + ";";
      return one_lexem;
    }
  void write_lexeme_in_file() override
  {

  }
    
};


string generate_sensors_data(LightSensors& A, const int total_le)
{
    string sensors_data ;
    for (int i = 0; i < total_le; i++)
    {
        if (((i % 5) == 0) && (i != 0))
        {
            sensors_data = sensors_data + "\n";
        }
            sensors_data = sensors_data + A.generate_one_lexeme(/*i*/);            
    }
    cout << sensors_data << endl;
    return sensors_data;

}

void write_sensors_data_in_file(string sensors_data)
{

    ofstream in_file("C:\\Users\\Kek\\Desktop\\Total_sensors_data.txt"/*, ios::app*/);//*
    if (in_file.is_open())
    {
        in_file << sensors_data << std::endl;
    }
    in_file.close();
}

///-----------------Class SmartItem
class ICleverItem
{
   virtual void get_string( ) = 0;
   virtual string set_string() = 0;
   virtual void parse_string() = 0;
};

class SmartLight:public ICleverItem
{
public:
    
    string data_from_file ="\0";
    map<string, int> characteristics;
    int total_characteristics = 0;
  
    
   void get_string() override
    {
       string tmp_string_for_getline = "\0";
        ifstream in("C:\\Users\\Kek\\Desktop\\Total_sensors_data.txt", ios::in); // окрываем файл для чтения
        if (in.is_open())
        {
            while (getline(in, tmp_string_for_getline))
            {
                if (tmp_string_for_getline != "\0") 
                {
                    data_from_file = tmp_string_for_getline;
                }
               cout <<"get_string\n\n"<< tmp_string_for_getline << endl;
            }
        }
        in.close();
       
    }
    string set_string() override
    {
        return "\0";
    }

    void parse_string() override
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


 
    

    float degree = 0;                   //Процентное значение выражающее состояние
    float max_value = 1, min_value = 0; //Максимальное и минимальное значения состояния
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



    float get_degree() //Получение значения состояния
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

   /* string generate_one_le(int size);
    string generate_data(const int total_le);
    void write_data_in_file();*/

};

//void SmartLight::write_data_in_file()
//{
//    ofstream in_file("C:\\Users\\Kek\\Desktop\\Smart_things_data.txt", ios::app);
//    if (in_file.is_open())
//    {
//        in_file <<this->total_data << std::endl;
//    }
//    in_file.close();
//}
//
//
//string SmartLight::generate_data(const int total_le)
//{
//    for (int i = 0; i < total_le; i++)
//    {
//        if((i%8)==0)
//        {
//            total_data = total_data + "\n";
//        }
//        total_data = total_data+generate_one_le(1);
//
//    }
//    cout <<"\n"<<this->total_data << endl;
//    return total_data;
//}
//
//
//string SmartLight::generate_one_le(const int size)
//{
// 
//    string tmp_string = "\0";
//    int tmp_propertie = 0,tmp_on_off=0;
//
//    string one_lexeme = "\0";
//  
//    for (int i = 0,j=0; i < size; i++)
//    {
//            if (one_lexeme[i] == ';' || i == 0)
//            {
//                tmp_propertie = rand() % 2;
//                tmp_on_off = rand() % 2;
//
//                if (tmp_propertie == 0)
//                {
//                    if (tmp_on_off == ON)
//                    {
//                        tmp_string = "p_of_li";
//                        tmp_string = tmp_string + "=";
//                        tmp_propertie = rand() % 101;
//                        tmp_string = tmp_string + to_string(tmp_propertie) + ";";
//                    }
//                    else
//                    {
//                        tmp_string = "L_OFF; ";
//                    }
//                }
//                else if (tmp_propertie == 1)
//                {
//                    if (tmp_on_off == ON)
//                    {
//                        tmp_string = "jls_open";
//                        tmp_string = tmp_string + "=";
//                        tmp_propertie = rand() % 101;
//                        tmp_string = tmp_string + to_string(tmp_propertie) + ";";
//                    }
//                    else
//                    {
//                    
//                        tmp_string = "JL_cl; ";
//                    }
//                }
//
//                
//                one_lexeme = one_lexeme + tmp_string;
//            }
//    }
//    return one_lexeme;
//
//}


//Класс умная лампочка
class SmartLamp : public SmartLight
{

    float max_value =500, min_value = 20;
    map<string, int> smart_lamp_char;
    int power_of_light = 0;

public:

    void set_p_of_li()
    {
        map<string, int> ::iterator it;
        it = characteristics.find("power_of_light");
        power_of_light = it->second;
    }
    void print_info() override
    {
              
       cout << "Set Brightness is " << power_of_light << " Lux" << endl;
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