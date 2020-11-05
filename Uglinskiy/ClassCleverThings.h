#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

enum ON_OFF {OFF=0,ON=1};

class ICleverItem
{
   virtual void get_string() = 0;
   virtual string set_string() = 0;
};

class SmartLight:public ICleverItem
{
protected:
    void get_string() override
    {

    }
    string set_string() override
    {
        return "\0";
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

public:
    string total_data ="\0";
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

    string generate_one_le(int size);
    string generate_data(const int total_le);
    void write_data_in_file();

};

void SmartLight::write_data_in_file()
{
    ofstream in_file("C:\\Users\\Kek\\Desktop\\Smart_things_data.txt", ios::app);
    if (in_file.is_open())
    {
        in_file <<this->total_data << std::endl;
    }
    in_file.close();
}


string SmartLight::generate_data(const int total_le)
{
    for (int i = 0; i < total_le; i++)
    {
        if((i%8)==0)
        {
            total_data = total_data + "\n";
        }
        total_data = total_data+generate_one_le(1);

    }
    cout <<"\n"<<this->total_data << endl;
    return total_data;
}


string SmartLight::generate_one_le(const int size)
{
    srand(time(NULL));
    string tmp_string = "\0";
    int tmp_propertie = 0,tmp_on_off=0;

    string one_lexeme = "\0";
  
    for (int i = 0,j=0; i < size; i++)
    {
            if (one_lexeme[i] == ';' || i == 0)
            {
                tmp_propertie = rand() % 2;
                tmp_on_off = rand() % 2;

                if (tmp_propertie == 0)
                {
                    if (tmp_on_off == ON)
                    {
                        tmp_string = "p_of_li";
                        tmp_string = tmp_string + "=";
                        tmp_propertie = rand() % 101;
                        tmp_string = tmp_string + to_string(tmp_propertie) + ";";
                    }
                    else
                    {
                        tmp_string = "L_OFF; ";
                    }
                }
                else if (tmp_propertie == 1)
                {
                    if (tmp_on_off == ON)
                    {
                        tmp_string = "jls_open";
                        tmp_string = tmp_string + "=";
                        tmp_propertie = rand() % 101;
                        tmp_string = tmp_string + to_string(tmp_propertie) + ";";
                    }
                    else
                    {
                    
                        tmp_string = "JL_cl; ";
                    }
                }

                
                one_lexeme = one_lexeme + tmp_string;
            }
    }
    return one_lexeme;

}


//Класс умная лампочка
class SmartLamp : public SmartLight
{

    float max_value = 1200, min_value = 100;

public:
    SmartLamp()
    {
        print_info();
    };

    void print_info() override
    {
        cout << "Set Brightness is " << this->degree * (max_value - min_value) / 100 << " Lumens" << endl;
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