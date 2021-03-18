#pragma once

#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include<Windows.h>
#define MAX_LAMP_LUMEN_FLOW 700
#define MAX_LAMP_POWER 12

using namespace std;

//��������� �������
class ISensors
{
	virtual string get_string() = 0;//��������� � �������� ������ � �������� ���������� ��������
	virtual void set_parameter(string what, int value) = 0;//���������� �������� ���� �� �����
	virtual float get_parameter(string what) = 0;//�������� �������� ���� �� �����
};

//����� �������
class Sensors : public ISensors
{
protected:
	map<string, int> sensors;//���� ��������
public:

	string get_string() override;

	void set_parameter(string what, int value) override//������������ �������� value  �� ����� what
	{
		sensors[what] = value;
	}

	float get_parameter(string what) override//��������  ��������  �� ����� what
	{
		return sensors[what];
	}
};

//����� ������� �����
class LightSensors : public Sensors
{
public:

	LightSensors()
	{
		sensors.insert(make_pair("BT", 0));
		sensors.insert(make_pair("SR", 0));
		sensors.insert(make_pair("LR", 0));
		sensors.insert(make_pair("KN", 0));
		sensors.insert(make_pair("OUT", 0));
	}
};

//����� ������� �����������
class TemperatureSensors : public Sensors
{
public:

	TemperatureSensors()
	{
		sensors.insert(make_pair("BT", 0));
		sensors.insert(make_pair("SR", 0));
		sensors.insert(make_pair("KN", 0));
		sensors.insert(make_pair("LR", 0));
	}
};

//����� ������� ���������
class HumiditySensors : public Sensors
{
public:

	HumiditySensors()
	{
		sensors.insert(make_pair("BT", 0));
		sensors.insert(make_pair("SR", 0));
		sensors.insert(make_pair("KN", 0));
		sensors.insert(make_pair("LR", 0));
	}
};


//��������� ����� �������
class ISmartItem
{
public:
	virtual void set_parameter(string, int) = 0;//���������� �������� ����  �� �����
	virtual void set_location(string) = 0;		//���������� ��������������� �������
	virtual void set_item_number(int) = 0;		//���������� ����� �������
	virtual int get_parameter(string) = 0;		//�������� �������� ���� �� �����
	virtual string get_location() = 0;			//�������� ��������������� �������
	virtual int get_item_number() = 0;			//������� ����� �������
	virtual string get_string() = 0;			//��������� � ������� ������ � �������� ���������� �����
};

//����� ����� ����
class SmartLight : public ISmartItem
{
protected:
	map<string, int> smart_thing_char;// ����-�������������� ����� ����
	string location = "\0";
	int number = 0;

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

class TheSun : public SmartLight
{
public:
	TheSun()
	{
	smart_thing_char.insert(make_pair("BR", 0));
	}
	int calculate_brightness(void);
};

//����� ����� ��������
class SmartLamp : public SmartLight
{
private:

public:
	SmartLamp()
	{
		smart_thing_char.insert(make_pair("R", 0));
		smart_thing_char.insert(make_pair("G", 0));
		smart_thing_char.insert(make_pair("B", 0));
		smart_thing_char.insert(make_pair("BR", 5));
	}
};

//����� ����� ������
class SmartJalousie : public SmartLight
{
private:

public:
	SmartJalousie()
	{
		smart_thing_char.insert(make_pair("DEG", 0));
	}
};

//����� ������������������ ��������
class SmartTemperatureRegulationThigs : public ISmartItem
{

};

//����� ����� �������
class SmartBatterey : public SmartTemperatureRegulationThigs
{

};


class IServerInfoWorker
{
	virtual string read_data() = 0;
	virtual void save_data(string string_to_file) = 0;
};

class ServerInfoFileWorker : public IServerInfoWorker
{
public:
	//������ ������ �� �����
	string read_data() override;

	//������ ������ � ����
	void save_data(string string_to_file) override;
};

//����� ��������
class SmartHouseManager
{
private:
	//������ ������ �������
	LightSensors LS;
	TemperatureSensors TS;
	HumiditySensors HS;

	//������ ������� ����� ����
	vector<SmartLamp> smart_lamps_vec;
	vector<SmartJalousie> smart_jalousie_vec;

	TheSun SUN;
	//������ ����� ������ � �������
	ServerInfoFileWorker FW;

	//������������� ������ ���� � �����,�������� (string)"123"->(int)123
	int parse_value(int start_index, string value_from_datafile);
	
	//������:���������� ������ �������� � ������� ������ ��� ���������� ����� �����
	void exception_out_of_range();
	
public:
	SmartHouseManager(int lenght_lamps = 1, int lenght_jalousie = 1)//����������� 
	{
		//������������� ��������� ����� �����
		smart_lamps_vec.resize(lenght_lamps);
		smart_jalousie_vec.resize(lenght_jalousie);
	}
	

	 //������
	void parse_string();
	
	//������ �������� �������� � ����������� �� ������ ����� ����� � ������ 
	void set_sensors_data();

	//������� ��� ������ � ���� ������
	string collect_all_data();
	
	//���� ���� ���������
	void one_cycle();
	
};