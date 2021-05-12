#pragma once

#include "TSmartItem.h"

class TSmartHumidifier : public TSmartItem
{

private:

public:
	TSmartHumidifier()
	{
		smart_thing_char.insert(make_pair("power", 100));
	}
};