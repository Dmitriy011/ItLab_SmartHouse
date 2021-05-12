#pragma once
#include "TSmartItem.h"

#define MAX_LAMP_LUMEN_FLOW 1200
#define MAX_LAMP_POWER 11

//Класс умная лампочка
class TSmartLamp : public TSmartItem
{
private:

public:
	TSmartLamp()
	{
		smart_thing_char.insert(make_pair("power", 5));
	}
};