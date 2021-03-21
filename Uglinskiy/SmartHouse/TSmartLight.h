﻿#pragma once
#include "ISmartItem.h"


using std::string;
using std::map;
using std::to_string;
using std::make_pair;
//Класс умный свет
class TSmartLight : public ISmartItem
{
protected:
	map<string, int> smart_thing_char;	// мапа-характеристики умной вещи
	string location = "\0";				//местонахождение объекта
	int number = 0;						//номер объекта 

public:
	void set_parameter(string what, int value) override//устанвливаем значение value  по ключу what
	{
		smart_thing_char[what] = value;
	}
	//Сеттеры и геттеры
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

