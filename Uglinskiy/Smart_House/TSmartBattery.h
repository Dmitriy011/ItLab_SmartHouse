#pragma once
#include "TSmartItem.h"

//����� ����� �������
class TSmartBattery :
    public TSmartItem
{
public:
	TSmartBattery()
	{
		smart_thing_char.insert(make_pair("power", 1200));	
	}
};

