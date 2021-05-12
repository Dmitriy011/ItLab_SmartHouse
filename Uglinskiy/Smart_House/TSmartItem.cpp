#include "TSmartItem.h"

//������� ��� ��������� ������ � ������ � ���� "����"="��������",
string TSmartItem::get_string()
{
	string return_string = "\0";	//������ ������ ������

	map<string, int>::iterator it;	//������ �������� 
	it = smart_thing_char.begin();	//������������� �������� � ������ ����

	while (it != smart_thing_char.end())//����: ���� �� ��������� ����� ����
	{
		return_string += it->first + "=" + to_string(it->second) + ',';//��������� � ������� ������: "���� = �������� �����,"
		++it;
		if (it == smart_thing_char.end())//������� ��������� �������� �������
		{
			return_string.erase(return_string.size() - 1);//����� ��������,�� �������� �� ����� 
		}
	}
	return return_string;
}
