#pragma once
#include "TSensors.h"
//класс датчики температуры
class TTemperatureSensors : public TSensors
{
public:
	//конструктор
	TTemperatureSensors()
	{
		sensors.insert(make_pair("BT", 0));
		sensors.insert(make_pair("SR", 0));
		sensors.insert(make_pair("KN", 0));
		sensors.insert(make_pair("LR", 0));
	}
};
