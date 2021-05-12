#pragma once
#include "TSmartItem.h"
//класс умное жалюзи
class TSmartJalousie : public TSmartItem
{
private:

public:
	TSmartJalousie()
	{
		smart_thing_char.insert(make_pair("rotation", 0));		
	}
};