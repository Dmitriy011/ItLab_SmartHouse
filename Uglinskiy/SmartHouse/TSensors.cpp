#include "TSensors.h"

//������� ��� ��������� ������ � ������ � ���� "����"="��������",
string TSensors::get_string()
{

	string tmp_string = "\0";		//������ ������ ������
	map<string, int>::iterator it;	//������ ��������

	it = sensors.begin();			//������������� �������� � ������
	
	while (it != sensors.end())//����: ���� �� ��������� ����� ����
	{
		tmp_string += it->first + "=" + to_string(it->second) + ',';//��������� � ������� ������: "���� = �������� �����,"
		++it;
		if (it == sensors.end())//������� ��������� �������� �������
		{
			tmp_string.erase(tmp_string.size() - 1);//����� ��������,�� �������� �� ����� 
		}
	}
	return tmp_string;//���������� ���������� ������
}