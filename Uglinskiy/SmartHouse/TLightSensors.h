#pragma once
#include "TSensors.h"
//����� ������� �����
class TLightSensors : public TSensors
{
public:
	//�����������
	TLightSensors()
	{
		sensors.insert(make_pair("BT", 0));
		sensors.insert(make_pair("SR", 0));
		sensors.insert(make_pair("LR", 0));
		sensors.insert(make_pair("KN", 0));
		sensors.insert(make_pair("OUT", 0));
	}
};
