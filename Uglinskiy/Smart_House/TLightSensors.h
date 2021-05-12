#pragma once
#include "TSensors.h"
//класс датчики света
class TLightSensors : public TSensors
{
public:
	//конструктор
	TLightSensors()
	{
		sensors.insert(make_pair("bath", 0));
		sensors.insert(make_pair("bed", 0));
		sensors.insert(make_pair("kitchen", 0));
		sensors.insert(make_pair("living", 0));
		sensors.insert(make_pair("OUT", 0));
	}
};
