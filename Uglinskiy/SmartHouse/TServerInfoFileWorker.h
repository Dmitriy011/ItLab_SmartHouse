#pragma once
#include "IServerInfoWorker.h"

class TServerInfoFileWorker : public IServerInfoWorker
{
public:
	//Чтение данных из файла
	string read_data() override;

	//Запись данных в файл
	void save_data(string string_to_file) override;
};

