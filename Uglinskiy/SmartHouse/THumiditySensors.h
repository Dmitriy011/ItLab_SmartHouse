#pragma once
#include "TSensors.h"
//класс датчики влажности
class THumiditySensors : public TSensors
{
public:
	//конструктор
	THumiditySensors()
	{
		sensors.insert(make_pair("BT", 0));
		sensors.insert(make_pair("SR", 0));
		sensors.insert(make_pair("KN", 0));
		sensors.insert(make_pair("LR", 0));
	}
};
