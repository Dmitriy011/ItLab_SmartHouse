#pragma once
#include <string>
using std::string;
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