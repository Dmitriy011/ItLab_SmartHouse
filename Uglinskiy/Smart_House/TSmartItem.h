#pragma once
#include "ISmartItem.h"

using std::string;
using std::map;
using std::to_string;
using std::make_pair;


class TSmartItem : public ISmartItem
{
protected:
	map<string, int> smart_thing_char;	// ����-�������������� ����� ����
	string location = "\0";				//��������������� �������
	int number = 0;						//����� ������� 
public:
	void set_parameter(string what, int value) override//������������ �������� value  �� ����� what
	{
		smart_thing_char[what] = value;
	}

	void set_location(string loc) override
	{
		location = loc;
	}

	void set_item_number(int nmb) override
	{
		number = nmb;
	}


	string get_location() override
	{
		return location;
	}

	int get_item_number() override
	{
		return number;
	}

	int get_parameter(string what) override//��������  ��������  �� ����� what
	{
		return smart_thing_char[what];
	}

	string get_string() override;
};

