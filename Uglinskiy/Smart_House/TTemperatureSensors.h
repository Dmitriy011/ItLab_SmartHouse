#pragma once
#include "TSensors.h"
//класс датчики температуры
class TTemperatureSensors : public TSensors
{
public:
	//конструктор
	TTemperatureSensors()
	{
		sensors.insert(make_pair("bath", 20));
		sensors.insert(make_pair("bed", 13));
		sensors.insert(make_pair("kitchen", 15));
		sensors.insert(make_pair("living", 22));
		sensors.insert(make_pair("OUT",18));
	}
};
