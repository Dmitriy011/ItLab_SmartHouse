#include "TSmartItem.h"

//собрать все имеющиеся данные в строку в виде "ключ"="значение",
string TSmartItem::get_string()
{
	string return_string = "\0";	//создаём пустую строку

	map<string, int>::iterator it;	//создаём итератор 
	it = smart_thing_char.begin();	//устанавливаем итератор в начало мапы

	while (it != smart_thing_char.end())//Цикл: пока не достигнем конца мапы
	{
		return_string += it->first + "=" + to_string(it->second) + ',';//добавляем к текущей строке: "ключ = значение ключа,"
		++it;
		if (it == smart_thing_char.end())//убираем последнюю ненужную запятую
		{
			return_string.erase(return_string.size() - 1);//вроде работает,но выглядит не очень 
		}
	}
	return return_string;
}
