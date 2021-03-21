#pragma once
#include <string>
#include <map>
using std::string;
//��������� �������
class ISensors
{
	virtual string get_string() = 0;							//��������� � �������� ������ � �������� ���������� ��������
	virtual void set_parameter(string what, int value) = 0;		//���������� �������� ���� �� �����
	virtual float get_parameter(string what) = 0;				//�������� �������� ���� �� �����
};
