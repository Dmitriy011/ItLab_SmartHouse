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
	//������ ������� � ����������� �� ������� �����
	int calculate_brightness(void);
};
