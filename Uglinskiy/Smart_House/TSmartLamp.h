#pragma once
#include "TSmartItem.h"
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