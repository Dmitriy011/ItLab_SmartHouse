#pragma once

#include "TSmartItem.h"

#define MAX_HUMDIFIER_PERFORMANCE 250.0f //250 грамм в час (4.1 грамма в минуту)
//класс Умный увлажнитель
class TSmartHumidifier : public TSmartItem
{

private:

public:
	TSmartHumidifier()
	{
		smart_thing_char.insert(make_pair("power", 100));
	}
};