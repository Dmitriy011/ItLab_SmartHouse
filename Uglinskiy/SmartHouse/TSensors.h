#pragma once
#include "ISensors.h"


using std::map;
using std::string;
using std::to_string;

//����� �������
class TSensors : public ISensors
{
protected:
	map<string, int> sensors;//���� ��������
public:

	string get_string() override;

	void set_parameter(string what, int value) override//������������ �������� value  �� ����� what
	{
		sensors[what] = value;
	}

	float get_parameter(string what) override			//��������  ��������  �� ����� what
	{
		return sensors[what];
	}
};

