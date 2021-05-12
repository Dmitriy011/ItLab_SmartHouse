#include "TSensors.h"

//собрать все имеющиеся данные в строку в виде "ключ"="значение",
string TSensors::get_string()
{

	string tmp_string = "\0";		//создаём пустую строку
	map<string, long>::iterator it;	//создаём итератор

	it = sensors.begin();			//устанавливаем итератор в начало
	
	while (it != sensors.end())//Цикл: пока не достигнем конца мапы
	{
		tmp_string += it->first + "=" + to_string(it->second) + ',';//добавляем к текущей строке: "ключ = значение ключа,"
		++it;
		if (it == sensors.end())//убираем последнюю ненужную запятую
		{
			tmp_string.erase(tmp_string.size() - 1);//вроде работает,но выглядит не очень 
		}
	}
	return tmp_string;//возвращаем полученную строку
}