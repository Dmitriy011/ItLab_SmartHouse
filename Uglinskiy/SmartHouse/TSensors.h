#pragma once
#include "ISensors.h"


using std::map;
using std::string;
using std::to_string;

//класс датчики
class TSensors : public ISensors
{
protected:
	map<string, int> sensors;//мапа сенсоров
public:

	string get_string() override;

	void set_parameter(string what, int value) override//устанвливаем значение value  по ключу what
	{
		sensors[what] = value;
	}

	float get_parameter(string what) override			//получаем  значение  по ключу what
	{
		return sensors[what];
	}
};

