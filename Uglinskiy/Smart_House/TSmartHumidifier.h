#pragma once

#include "TSmartItem.h"

#define MAX_HUMDIFIER_PERFORMANCE 250.0f //250 ����� � ��� (4.1 ������ � ������)
//����� ����� �����������
class TSmartHumidifier : public TSmartItem
{

private:

public:
	TSmartHumidifier()
	{
		smart_thing_char.insert(make_pair("power", 100));
	}
};