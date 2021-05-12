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

#include "py_client.h"


//#include "TSmartLight.h"
#include "TTheSun.h"
#include "TSmartLamp.h"
#include "TSmartJalousie.h"
#include "TSmartBattery.h"
#include "TSmartHumidifier.h"


//#include "TSensors.h"
#include "TLightSensors.h"
#include "THumiditySensors.h"
#include "TTemperatureSensors.h"

#include "TRoom.h"


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
	vector<TSmartHumidifier> smart_humidifier_vec;
	//комнаты
	vector<TRoom> rooms_vec;

	//Солнце
	TTheSun SUN;

	
	
public:
	
	TSmartHouseManager(int lenght_lamps = 1, int lenght_jalousie = 1,int lenght_battery=1,int lenght_humidifier = 1, int number_of_rooms=4)//конструктор 
	{
		//инициализация количесва умных вещей
		smart_lamps_vec.resize(lenght_lamps);
		smart_jalousie_vec.resize(lenght_jalousie);
		smart_battery_vec.resize(lenght_battery);
		smart_humidifier_vec.resize(lenght_humidifier);
		//инициализация комнат
		TRoom KN(10.5,"kitchen");
		TRoom LR(25,"living");
		TRoom SR(15,"bed");
		TRoom BT(7.5,"bath");

		rooms_vec.push_back(KN);
		rooms_vec.push_back(LR);
		rooms_vec.push_back(SR);
		rooms_vec.push_back(BT);	
	}
	

	//чтение из базы данных
	void read_db();

	//Обсчёт значений датчиков в зависимости от работы умных вещей и солнца 
	void set_sensors_data();

	//Собрать все данные в одну строку

	string collect_all_data();

	//Один цикл программы
	void one_cycle();
	
};