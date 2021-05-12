#pragma once
#include "TSmartItem.h"

//класс умная батарея
class TSmartBattery :
    public TSmartItem
{
public:
	TSmartBattery()
	{
		smart_thing_char.insert(make_pair("power", 1200));	
	}
};

