#pragma once
#include "TSmartLight.h"
//����� ����� ������
class TSmartJalousie : public TSmartLight
{
private:

public:
	TSmartJalousie()
	{
		smart_thing_char.insert(make_pair("DEG", 0));
	}
};