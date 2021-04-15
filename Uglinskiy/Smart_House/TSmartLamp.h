#pragma once
#include "TSmartLight.h"
//Класс умная лампочка
class TSmartLamp : public TSmartLight
{
private:

public:
	TSmartLamp()
	{
		smart_thing_char.insert(make_pair("BR", 5));
		name = "lamp";
	}
};