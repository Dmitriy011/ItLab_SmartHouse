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


//#include "TSmartLight.h"
#include "TTheSun.h"
#include "TSmartLamp.h"
#include "TSmartJalousie.h"
#include "TSmartBattery.h"


//#include "TSensors.h"
#include "TLightSensors.h"
#include "THumiditySensors.h"
#include "TTemperatureSensors.h"

#include "TRoom.h"


#include "TServerInfoFileWorker.h"

using namespace std;

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
	vector<TSmartBattery> smart_battery_vec;
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
	//int number_of_rooms,int lenght_lamps = 1, int lenght_jalousie = 1,int lenght_battery=1
	TSmartHouseManager(int number_of_rooms,int lenght_lamps = 1, int lenght_jalousie = 1,int lenght_battery=1)//конструктор 
	{
		//инициализация солнца
		SUN.set_item_number(lenght_lamps+1);
		//инициализация количесва умных вещей
		smart_lamps_vec.resize(lenght_lamps);
		smart_jalousie_vec.resize(lenght_jalousie);
		smart_battery_vec.resize(lenght_battery);
		//инициализация комнат
		TRoom KN(18, 0.8, "KN");
		TRoom LR(25, 1, "LR");
		TRoom SR(20, 0.7, "SR");
		TRoom BT(10, 0, "BT");

		rooms_vec.push_back(KN);
		rooms_vec.push_back(LR);
		rooms_vec.push_back(SR);
		rooms_vec.push_back(BT);	
	}
	

	 //Парсер
	void parse_string();
	
	//Обсчёт значений датчиков в зависимости от работы умных вещей и солнца 
	void set_sensors_data();


	void insert_smart_lamp(TSmartLamp lamp_to_ins,string where_to_ins = "\0");

	void insert_smart_jalousie(TSmartJalousie jal_to_ins, string where_to_ins = "\0");

	void insert_smart_battery(TSmartBattery batt_to_ins, string where_to_ins = "\0");

	//Собрать все данные в одну строку
	string collect_all_data();
	
	//Один цикл программы
	void one_cycle();
	
};