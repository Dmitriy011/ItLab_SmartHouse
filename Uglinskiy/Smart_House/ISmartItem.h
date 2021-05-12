﻿#pragma once
//интерфейс умный предмет
#include <string>
#include <map>

using std::string;
#define MAX_LAMP_LUMEN_FLOW 1200
#define MAX_LAMP_POWER 11
#define OPTIMAL_METR_POWER 100
#define MAX_CALCULATED_HUMIDIFIER_S 25
#define MAX_HUMDIFIER_PERFORMANCE 250.0f //250 грамм в час (4.1 грамма в минуту)

class ISmartItem
{
public:
	virtual void set_parameter(string what, int value) = 0;//установить значение поля  по ключу
	virtual void set_location(string loc) = 0;		//установить местонахождения объекта
	virtual void set_item_number(int nmb) = 0;		//установить номер объекта
	virtual int get_parameter(string what) = 0;		//получить значения поля по ключу
	virtual string get_location() = 0;			//получить местонахождение объекта
	virtual int get_item_number() = 0;			//получть номер объекта
	virtual string get_string() = 0;			//составить и вернуть строку с текущими значениями полей
};

