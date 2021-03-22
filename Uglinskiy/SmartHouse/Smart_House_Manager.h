#pragma once

#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

#include<Windows.h>


#include "TSmartLight.h"
#include "TTheSun.h"
#include "TSmartLamp.h"
#include "TSmartJalousie.h"


#include "TSensors.h"
#include "TLightSensors.h"
#include "THumiditySensors.h"
#include "TTemperatureSensors.h"

#include "TRoom.h"


#include "TServerInfoFileWorker.h"



using namespace std;

//интерфейс датчики
//class ISensors
//{
//	virtual string get_string() = 0;							//составить и получить строку с текущими значениями датчиков
//	virtual void set_parameter(string what, int value) = 0;		//установить значение поля по ключу
//	virtual float get_parameter(string what) = 0;				//получить значение поля по ключу
//};

//класс датчики
//class TSensors : public ISensors
//{
//protected:
//	map<string, int> sensors;//мапа сенсоров
//public:
//
//	string get_string() override;
//
//	void set_parameter(string what, int value) override//устанвливаем значение value  по ключу what
//	{
//		sensors[what] = value;
//	}
//
//	float get_parameter(string what) override			//получаем  значение  по ключу what
//	{
//		return sensors[what];
//	}
//};

//класс датчики света
//class TLightSensors : public TSensors
//{
//public:
//	//конструктор
//	TLightSensors()
//	{
//		sensors.insert(make_pair("BT", 0));
//		sensors.insert(make_pair("SR", 0));
//		sensors.insert(make_pair("LR", 0));
//		sensors.insert(make_pair("KN", 0));
//		sensors.insert(make_pair("OUT", 0));
//	}
//};

//класс датчики температуры
//class TTemperatureSensors : public TSensors
//{
//public:
//	//конструктор
//	TTemperatureSensors()
//	{
//		sensors.insert(make_pair("BT", 0));
//		sensors.insert(make_pair("SR", 0));
//		sensors.insert(make_pair("KN", 0));
//		sensors.insert(make_pair("LR", 0));
//	}
//};

//класс датчики влажности
//class THumiditySensors : public TSensors
//{
//public:
//	//конструктор
//	THumiditySensors()
//	{
//		sensors.insert(make_pair("BT", 0));
//		sensors.insert(make_pair("SR", 0));
//		sensors.insert(make_pair("KN", 0));
//		sensors.insert(make_pair("LR", 0));
//	}
//};


//интерфейс умный предмет
//class ISmartItem
//{
//public:
//	virtual void set_parameter(string, int) = 0;//установить значение поля  по ключу
//	virtual void set_location(string) = 0;		//установить местонахождения объекта
//	virtual void set_item_number(int) = 0;		//установить номер объекта
//	virtual int get_parameter(string) = 0;		//получить значения поля по ключу
//	virtual string get_location() = 0;			//получить местонахождение объекта
//	virtual int get_item_number() = 0;			//получть номер объекта
//	virtual string get_string() = 0;			//составить и вернуть строку с текущими значениями полей
//};

//Класс умный свет
//class TSmartLight : public ISmartItem
//{
//protected:
//	map<string, int> smart_thing_char;	// мапа-характеристики умной вещи
//	string location = "\0";				//местонахождение объекта
//	int number = 0;						//номер объекта 
//
//public:
//	void set_parameter(string what, int value) override//устанвливаем значение value  по ключу what
//	{
//		smart_thing_char[what] = value;
//	}
//	//Сеттеры и геттеры
//	void set_location(string loc) override
//	{
//		location = loc;
//	}
//
//	void set_item_number(int nmb) override
//	{
//		number = nmb;
//	}
//
//	string get_location() override
//	{
//		return location;
//	}
//
//	int get_item_number() override
//	{
//		return number;
//	}
//
//	int get_parameter(string what) override//получаем  значение  по ключу what
//	{
//		return smart_thing_char[what];
//	}
//	string get_string() override;
//
//};

//class TTheSun : public TSmartLight
//{
//public:
//	TTheSun()
//	{
//	smart_thing_char.insert(make_pair("BR", 0));
//	}
//	//расчёт яркости в зависимости от времени суток
//	int calculate_brightness(void);
//};

//Класс умная лампочка
//class TSmartLamp : public TSmartLight
//{
//private:
//
//public:
//	TSmartLamp()
//	{
//		smart_thing_char.insert(make_pair("R", 0));
//		smart_thing_char.insert(make_pair("G", 0));
//		smart_thing_char.insert(make_pair("B", 0));
//		smart_thing_char.insert(make_pair("BR", 5));
//	}
//};

//класс умное жалюзи
//class TSmartJalousie : public TSmartLight
//{
//private:
//
//public:
//	TSmartJalousie()
//	{
//		smart_thing_char.insert(make_pair("DEG", 0));
//	}
//};

//Класс терморегуляционных приборов
//class TSmartTemperatureRegulationThigs : public ISmartItem
//{
//
//};
//
////Класс умная батарея
//class TSmartBatterey : public TSmartTemperatureRegulationThigs
//{
//
//};

//Класс Комната
//class TRoom
//{
//private:
//	float S = 1;//площадь
//	float sun_energy_percentage=1;//коэффициент отвечающий за то ,сколько света(энергии солнца) доходит до комнаты
//	string name = "\0";//имя
//public:
//	TRoom(float Sq = 1,float s_e_p=1,string nm="room")
//	{
//		S = Sq;
//		sun_energy_percentage = s_e_p;
//		name = nm;
//	}
//	//получить площаль
//	float get_S()
//	{
//		return S;
//	}
//	//получить коэффициент солнечной энергии
//	float get_sun_en_per()
//	{
//		return sun_energy_percentage;
//	}
//	//получить имя комнаты
//	string get_name()
//	{
//		return name;
//	}
//
//	////под вопросом нужны ли сэттеры
//	void set_S(float Sq)
//	{
//		S = Sq;
//	}
//	void set_sun_en_per(float s_e_p)
//	{
//		sun_energy_percentage = s_e_p;
//	}
//};

//class IServerInfoWorker
//{
//	virtual string read_data() = 0;						//Чтение данных из файла
//	virtual void save_data(string string_to_file) = 0;  //Запись данных в файл
//};

//class TServerInfoFileWorker : public IServerInfoWorker
//{
//public:
//	//Чтение данных из файла
//	string read_data() override;
//
//	//Запись данных в файл
//	void save_data(string string_to_file) override;
//};

//Класс Менеджер
class TSmartHouseManager
{
private:
	//создаём классы сенсоры
	TLightSensors LS;
	TTemperatureSensors TS;
	THumiditySensors HS;

	//создаём векторы умных вещей
	vector<TSmartLamp> smart_lamps_vec;//умные лампочки
	vector<TSmartJalousie> smart_jalousie_vec;//умные жалюзи
	
	//комнаты
	vector<TRoom> rooms_vec;

	//Солнце
	TTheSun SUN;

	//создаём класс работы с файлами
	TServerInfoFileWorker FW;

	//Распарсивание строки цифр в число,например (string)"123"->(int)123
	int parse_value(int start_index, string value_from_datafile);
	
	//Ошибка:количество данных принятых с сервера больше чем количество умных вещей
	void exception_out_of_range();
	
	
public:
	TSmartHouseManager(int number_of_rooms,int lenght_lamps = 1, int lenght_jalousie = 1)//конструктор 
	{
		//инициализация солнца
		SUN.set_item_number(lenght_lamps+1);
		//инициализация количесва умных вещей
		smart_lamps_vec.resize(lenght_lamps);
		smart_jalousie_vec.resize(lenght_jalousie);

		//инициализация комнат
		TRoom KN(18, 0.8, "KN");
		TRoom LR(25, 1, "LR");
		TRoom SR(20, 0.7, "SR");
		TRoom BT(12, 0, "BT");

		rooms_vec.push_back(KN);
		rooms_vec.push_back(LR);
		rooms_vec.push_back(SR);
		rooms_vec.push_back(BT);	
	}
	

	 //Парсер
	void parse_string();
	
	//Обсчёт значений датчиков в зависимости от работы умных вещей и солнца 
	void set_sensors_data();

	//Собрать все данные в одну строку
	string collect_all_data();
	
	//Один цикл программы
	void one_cycle();
	
};