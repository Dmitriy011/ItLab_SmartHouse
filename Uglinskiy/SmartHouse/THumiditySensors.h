#pragma once
#include "TSensors.h"
//����� ������� ���������
class THumiditySensors : public TSensors
{
public:
	//�����������
	THumiditySensors()
	{
		sensors.insert(make_pair("BT", 0));
		sensors.insert(make_pair("SR", 0));
		sensors.insert(make_pair("KN", 0));
		sensors.insert(make_pair("LR", 0));
	}
};
