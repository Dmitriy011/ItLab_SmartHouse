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
#define MAX_LAMP_LUMEN_FLOW 1200
#define MAX_LAMP_POWER 12

using namespace std;

//��������� �������
class ISensors
{
	virtual string get_string() = 0;							//��������� � �������� ������ � �������� ���������� ��������
	virtual void set_parameter(string what, int value) = 0;		//���������� �������� ���� �� �����
	virtual float get_parameter(string what) = 0;				//�������� �������� ���� �� �����
};

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
class TSmartLight : public ISmartItem
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
	//������� � �������
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

class TTheSun : public TSmartLight
{
public:
	TTheSun()
	{
	smart_thing_char.insert(make_pair("BR", 0));
	}
	//������ ������� � ����������� �� ������� �����
	int calculate_brightness(void);
};

//����� ����� ��������
class TSmartLamp : public TSmartLight
{
private:

public:
	TSmartLamp()
	{
		smart_thing_char.insert(make_pair("R", 0));
		smart_thing_char.insert(make_pair("G", 0));
		smart_thing_char.insert(make_pair("B", 0));
		smart_thing_char.insert(make_pair("BR", 5));
	}
};

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

//����� ������������������ ��������
class TSmartTemperatureRegulationThigs : public ISmartItem
{

};

//����� ����� �������
class TSmartBatterey : public TSmartTemperatureRegulationThigs
{

};

//����� �������
class TRoom
{
private:
	float S = 1;//�������
	float sun_energy_percentage=1;//����������� ���������� �� �� ,������� �����(������� ������) ������� �� �������
	string name = "\0";//���
public:
	TRoom(float Sq = 1,float s_e_p=1,string nm="room")
	{
		S = Sq;
		sun_energy_percentage = s_e_p;
		name = nm;
	}
	//�������� �������
	float get_S()
	{
		return S;
	}
	//�������� ����������� ��������� �������
	float get_sun_en_per()
	{
		return sun_energy_percentage;
	}
	//�������� ��� �������
	string get_name()
	{
		return name;
	}

	////��� �������� ����� �� �������
	void set_S(float Sq)
	{
		S = Sq;
	}
	void set_sun_en_per(float s_e_p)
	{
		sun_energy_percentage = s_e_p;
	}
};

class IServerInfoWorker
{
	virtual string read_data() = 0;						//������ ������ �� �����
	virtual void save_data(string string_to_file) = 0;  //������ ������ � ����
};

class TServerInfoFileWorker : public IServerInfoWorker
{
public:
	//������ ������ �� �����
	string read_data() override;

	//������ ������ � ����
	void save_data(string string_to_file) override;
};

//����� ��������
class TSmartHouseManager
{
private:
	//������ ������ �������
	TLightSensors LS;
	TTemperatureSensors TS;
	THumiditySensors HS;

	//������ ������� ����� �����
	vector<TSmartLamp> smart_lamps_vec;//����� ��������
	vector<TSmartJalousie> smart_jalousie_vec;//����� ������
	
	//�������
	vector<TRoom> rooms_vec;

	//������
	TTheSun SUN;

	//������ ����� ������ � �������
	TServerInfoFileWorker FW;

	//������������� ������ ���� � �����,�������� (string)"123"->(int)123
	int parse_value(int start_index, string value_from_datafile);
	
	//������:���������� ������ �������� � ������� ������ ��� ���������� ����� �����
	void exception_out_of_range();
	
	
public:
	TSmartHouseManager(int number_of_rooms,int lenght_lamps = 1, int lenght_jalousie = 1)//����������� 
	{
		//������������� ��������� ����� �����
		smart_lamps_vec.resize(lenght_lamps);
		smart_jalousie_vec.resize(lenght_jalousie);
		//������������� ������
		TRoom KN(18, 0.8, "KN");
		TRoom LR(25, 1, "LR");
		TRoom SR(20, 0.7, "SR");
		TRoom BT(12, 0, "BT");

		rooms_vec.push_back(KN);
		rooms_vec.push_back(LR);
		rooms_vec.push_back(SR);
		rooms_vec.push_back(BT);	
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