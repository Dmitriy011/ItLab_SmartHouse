#pragma once
#include "TSmartLight.h"
class TTheSun : public TSmartLight
{
public:
	TTheSun()
	{
	smart_thing_char.insert(make_pair("BR", 0));
	location = "SU";
	}
	//расчёт яркости в зависимости от времени суток
	int calculate_brightness(void);
};
