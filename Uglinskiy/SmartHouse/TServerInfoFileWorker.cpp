#include "TServerInfoFileWorker.h"
#pragma warning(disable : 4996)
//�������� ������ �� ����� � ������� �� � ���� ������
string TServerInfoFileWorker::read_data()
{
	ifstream in("smart_lamp.txt", ios::in); // �������� ���� ��� ������

	std::stringstream sstr;
	sstr << in.rdbuf();
	return sstr.str();
}

//��������� ������ � ����
void TServerInfoFileWorker::save_data(string string_to_file)
{
	time_t now = time(NULL);//������ ��������� �������

	ofstream in_file("Total_sensors_data.txt");
	if (in_file.is_open())
	{

		in_file << asctime(localtime(&now));//���������� ������� �����
		cout << asctime(localtime(&now));
		in_file << string_to_file << endl;	//���������� ������ �� �������� ������ � ����

		cout << string_to_file << endl;
	}
	in_file.close();//��������� ����
}