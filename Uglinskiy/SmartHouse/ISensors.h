#pragma once
#include <string>
#include <map>
using std::string;
//интерфейс датчики
class ISensors
{
	virtual string get_string() = 0;							//составить и получить строку с текущими значениями датчиков
	virtual void set_parameter(string what, int value) = 0;		//установить значение поля по ключу
	virtual float get_parameter(string what) = 0;				//получить значение поля по ключу
};
