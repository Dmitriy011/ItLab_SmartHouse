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
#define MAX_LAMP_LUMEN_FLOW 700
#define MAX_LAMP_POWER 12

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

	string get_string() override;

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
		sensors.insert(make_pair("BT", 0));
		sensors.insert(make_pair("SR", 0));
		sensors.insert(make_pair("LR", 0));
		sensors.insert(make_pair("KN", 0));
		sensors.insert(make_pair("OUT", 0));
	}
};

//класс датчики температуры
class TemperatureSensors : public Sensors
{
public:

	TemperatureSensors()
	{
		sensors.insert(make_pair("BT", 0));
		sensors.insert(make_pair("SR", 0));
		sensors.insert(make_pair("KN", 0));
		sensors.insert(make_pair("LR", 0));
	}
};

//класс датчики влажности
class HumiditySensors : public Sensors
{
public:

	HumiditySensors()
	{
		sensors.insert(make_pair("BT", 0));
		sensors.insert(make_pair("SR", 0));
		sensors.insert(make_pair("KN", 0));
		sensors.insert(make_pair("LR", 0));
	}
};


//интерфейс умный предмет
class ISmartItem
{
public:
	virtual void set_parameter(string, int) = 0;//установить значение поля  по ключу
	virtual void set_location(string) = 0;		//установить местонахождения объекта
	virtual void set_item_number(int) = 0;		//установить номер объекта
	virtual int get_parameter(string) = 0;		//получить значения поля по ключу
	virtual string get_location() = 0;			//получить местонахождение объекта
	virtual int get_item_number() = 0;			//получть номер объекта
	virtual string get_string() = 0;			//составить и вернуть строку с текущими значениями полей
};

//Класс умный свет
class SmartLight : public ISmartItem
{
protected:
	map<string, int> smart_thing_char;// мапа-характеристики умной вещи
	string location = "\0";
	int number = 0;

public:
	void set_parameter(string what, int value) override//устанвливаем значение value  по ключу what
	{
		smart_thing_char[what] = value;
	}
	void set_location(string loc) override
	{
		location = loc;
	}

	void set_item_number(int nmb) override
	{
		number = nmb;
	}

	string get_location() override
	{
		return location;
	}

	int get_item_number() override
	{
		return number;
	}

	int get_parameter(string what) override//получаем  значение  по ключу what
	{
		return smart_thing_char[what];
	}
	string get_string() override;

};

class TheSun : public SmartLight
{
public:
	TheSun()
	{
	smart_thing_char.insert(make_pair("BR", 0));
	}
	int calculate_brightness(void);
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

//Класс терморегуляционных приборов
class SmartTemperatureRegulationThigs : public ISmartItem
{

};

//Класс умная батарея
class SmartBatterey : public SmartTemperatureRegulationThigs
{

};


class IServerInfoWorker
{
	virtual string read_data() = 0;
	virtual void save_data(string string_to_file) = 0;
};

class ServerInfoFileWorker : public IServerInfoWorker
{
public:
	//Чтение данных из файла
	string read_data() override;

	//Запись данных в файл
	void save_data(string string_to_file) override;
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

	TheSun SUN;
	//создаём класс работы с файлами
	ServerInfoFileWorker FW;

	//Распарсивание строки цифр в число,например (string)"123"->(int)123
	int parse_value(int start_index, string value_from_datafile);
	
	//Ошибка:количество данных принятых с сервера больше чем количество умных вещей
	void exception_out_of_range();
	
public:
	SmartHouseManager(int lenght_lamps = 1, int lenght_jalousie = 1)//конструктор 
	{
		//инициализация количесва умных вещей
		smart_lamps_vec.resize(lenght_lamps);
		smart_jalousie_vec.resize(lenght_jalousie);
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