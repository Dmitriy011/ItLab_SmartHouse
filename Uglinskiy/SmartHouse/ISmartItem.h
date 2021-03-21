#pragma once
//��������� ����� �������
#include <string>
#include <map>

using std::string;
#define MAX_LAMP_LUMEN_FLOW 1200
#define MAX_LAMP_POWER 12

class ISmartItem
{
public:
	virtual void set_parameter(string what, int value) = 0;//���������� �������� ����  �� �����
	virtual void set_location(string loc) = 0;		//���������� ��������������� �������
	virtual void set_item_number(int nmb) = 0;		//���������� ����� �������
	virtual int get_parameter(string what) = 0;		//�������� �������� ���� �� �����
	virtual string get_location() = 0;			//�������� ��������������� �������
	virtual int get_item_number() = 0;			//������� ����� �������
	virtual string get_string() = 0;			//��������� � ������� ������ � �������� ���������� �����
};

