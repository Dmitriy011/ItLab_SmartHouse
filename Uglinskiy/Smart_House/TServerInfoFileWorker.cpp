#include "TServerInfoFileWorker.h"
#pragma warning(disable : 4996)
//прочесть данные из файла и вернуть их в виде строки
string TServerInfoFileWorker::read_data()
{
	ifstream in("smart_lamp.txt", ios::in); // окрываем файл для чтения

	std::stringstream sstr;
	sstr << in.rdbuf();
	return sstr.str();
}

//сохранить данные в файл
void TServerInfoFileWorker::save_data(string string_to_file)
{
	time_t now = time(NULL);//создаём переменую времени

	ofstream in_file("Total_sensors_data.txt");
	if (in_file.is_open())
	{

		in_file << asctime(localtime(&now));//Записываем текущее время
		cout << asctime(localtime(&now));
		in_file << string_to_file << endl;	//записываем данные из принятой строки в файл

		cout << string_to_file << endl;
	}
	in_file.close();//закрываем файл
}