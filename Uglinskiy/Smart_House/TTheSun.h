#pragma once
#include "TSmartItem.h"
class TTheSun : public TSmartItem
{
public:
	TTheSun()
	{
	smart_thing_char.insert(make_pair("power", 0));
	location = "sun";
	}
	//расчёт яркости в зависимости от времени суток
	int calculate_brightness(void);
};
