#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iostream>
using namespace std;



class IServerInfoWorker
{
	virtual string read_data() = 0;						//������ ������ �� �����
	virtual void save_data(string string_to_file) = 0;  //������ ������ � ����
};
