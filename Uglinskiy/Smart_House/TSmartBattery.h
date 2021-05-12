#pragma once
#include "TSmartItem.h"
#define ONE_BATTERY_MAX_POWER 2500
class TSmartBattery :
    public TSmartItem
{
public:
	TSmartBattery()
	{
		smart_thing_char.insert(make_pair("power", ONE_BATTERY_MAX_POWER));	
	}
};

