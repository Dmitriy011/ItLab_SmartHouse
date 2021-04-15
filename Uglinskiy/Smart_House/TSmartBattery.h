#pragma once
#include "TSmartHeaters.h"
#define ONE_BATTERY_MAX_POWER 6*200
class TSmartBattery :
    public TSmartHeaters
{
public:
	TSmartBattery()
	{
		smart_thing_char.insert(make_pair("power", ONE_BATTERY_MAX_POWER));
		name = "battery";
	}
};

