#pragma once
#include "TSensors.h"
//����� ������� �����������
class TTemperatureSensors : public TSensors
{
public:
	//�����������
	TTemperatureSensors()
	{
		sensors.insert(make_pair("BT", 0));
		sensors.insert(make_pair("SR", 0));
		sensors.insert(make_pair("KN", 0));
		sensors.insert(make_pair("LR", 0));
	}
};
