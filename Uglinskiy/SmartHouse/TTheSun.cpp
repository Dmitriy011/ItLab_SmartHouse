#include "TTheSun.h"
#include <ctime>

using std::clock;
//������ ������� ������ � ����������� �� �����
int TTheSun::calculate_brightness()
{
	int day_lenght = 15, half_day_lenght = 0;		//������ ���������� ����������������� ����� � ����������������� �������� ����� � ��������	
	int day_time = (clock() / 1000) % (day_lenght);	//������ ���������� ,����������� �� ������� ����� ����� � ��������
	//��� ������������� �� ��������� �������:������ ����� ��������� �� ������ ��������� � ��������
	//� �� ���� ���� ������� �� ������� �� ����������������� �����
	//��������� ����� ���������� ������������ ����� �� ���������� ������ ���������.���� ���� ����� day_lenght
	int time_to_night = 0;//���������� ���������� �� ��������� ���������� ������ �� 00:00.�� ����� ���� ������ half_day_lenght
	float sun_brightness_to_daytime_koeff = 0;		//����������� ���������� �� ��,������� ������� ������ ������ ����� �������� ������� ������ �� 1 �.�.
	half_day_lenght = day_lenght / 2;				//����������� �������� �����

	if (day_time <= half_day_lenght)//���� ����� ������ ������� �� ������ ���������� �������� day_time  �  time_to_night
	{
		time_to_night = day_time;
	}
	else//����� ����������� ������� ������� ������� �� ����������� 00:00
	{
		if (day_time != 0)
		{
			time_to_night = day_lenght - day_time;
		}
		else
		{
			time_to_night = 0;
		}
	}
	sun_brightness_to_daytime_koeff = (float)half_day_lenght / MAX_LAMP_POWER;
	return (time_to_night / sun_brightness_to_daytime_koeff);//���������� ������� � �.�.
}