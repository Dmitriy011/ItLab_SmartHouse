#pragma once
#include "IServerInfoWorker.h"

class TServerInfoFileWorker : public IServerInfoWorker
{
public:
	//������ ������ �� �����
	string read_data() override;

	//������ ������ � ����
	void save_data(string string_to_file) override;
};

