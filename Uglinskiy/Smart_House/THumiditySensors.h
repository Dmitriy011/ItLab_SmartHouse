#pragma once
#include "TSensors.h"
//класс датчики влажности
class THumiditySensors : public TSensors
{
public:
	//конструктор
	THumiditySensors()
	{
		sensors.insert(make_pair("bath", 0));
		sensors.insert(make_pair("bed", 0));
		sensors.insert(make_pair("kitchen", 0));
		sensors.insert(make_pair("living", 0));
	}
};
