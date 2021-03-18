#include "Smart_House_Manager.h"


//собрать все имеющиеся данные в строку в виде "ключ"="значение",
string Sensors::get_string()
{

	string tmp_string = "\0";//создаём пустую строку
	map<string, int>::iterator it;//создаём итератор

	it = sensors.begin();//устанавливаем итератор в начало

	while (it != sensors.end())//Цикл: пока не достигнем конца мапы
	{
		tmp_string += it->first + "=" + to_string(it->second) + ',';//добавляем к текущей строке: "ключ = значение ключа,"
		++it;
		if (it == sensors.end())//убираем последнюю ненужную запятую
		{
			tmp_string.erase(tmp_string.size() - 1);//вроде работает,но выглядит не очень 
		}
	}
	return tmp_string;
}

//собрать все имеющиеся данные в строку в виде "ключ"="значение",
string SmartLight::get_string()
{
	string return_string = "\0";//создаём пустую строку

	map<string, int>::iterator it;//создаём итератор 
	it = smart_thing_char.begin();//устанавливаем итератор в начало мапы

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

//расчёт яркости солнца в зависимости от лонца
int TheSun::calculate_brightness()
{
	int day_lenght = 15, half_day_lenght = 0;	//создаём переменны продолжительность суток и продолжительность половины суток в секундах	
	int day_time = (clock() / 1000) % (day_lenght);//создаём переменную ,отвечаующую за текущее время суток в секундах
	//оно высчитывается по следующей формуле:Берётся время прошедшее от начала программы в секундах
	//и от него берём остаток от деления на продолжительность суток
	//Благодаря этому добиваемся зацикливания суток на протяжении работы программы.Один цикл равен day_lenght
	int time_to_night = 0;//переменная отвечающая за ближайшее количество секунд до 00:00.Не может быть больше half_day_lenght
	float sun_brightness_to_daytime_koeff = 0;//коэффициент отвачающий за то,сколько времени должно пройти чтобы изменить яркость солнца на 1 
	half_day_lenght = day_lenght / 2;//высчитываем половину суток

	if (day_time <= half_day_lenght)//если время меньше полудня то просто записываем значение day_time  в  time_to_night
	{
		time_to_night = day_time;
	}
	else//иначе высчитываем сколько времени остаётся до наступления 00:00
	{
		if (day_time != 0)
		{
			time_to_night = day_lenght - day_time;
		}
		else
		{
			time_to_night = 0;
		}
	}
	sun_brightness_to_daytime_koeff = (float)half_day_lenght / MAX_LAMP_POWER;
	return (time_to_night / sun_brightness_to_daytime_koeff);//возвращаем яркость в у.е.
}

//прочесть данные из файла и вернуть их в виде строки
string ServerInfoFileWorker::read_data()
{
	ifstream in("smart_lamp.txt", ios::in); // окрываем файл для чтения

	std::stringstream sstr;
	sstr << in.rdbuf();
	return sstr.str();
}

//сохранить данные в файл
void ServerInfoFileWorker::save_data(string string_to_file)
{
	time_t now = time(NULL);//создаём переменую времени

	ofstream in_file("Total_sensors_data.txt");
	if (in_file.is_open())
	{

		in_file << asctime(localtime(&now));//Записываем текущее время
		cout << asctime(localtime(&now));
		in_file << string_to_file << endl;//записываем данные из принятой строки в файл

		cout << string_to_file << endl;
	}
	in_file.close();//закрываем файл
}

//Ошибка:количество данных принятых с сервера больше чем количество умных вещей
void SmartHouseManager::exception_out_of_range()
{
	cout << "ERROR: the number of smart things received from the server is greater than it really exists : the program is closing" << "\n";
	exit(1);
}

//Распарсивание строки цифр в число,например (string)"123"->(int)123
int SmartHouseManager::parse_value(int start_index, string value_from_datafile)
{
	int i = start_index;
	string tmp_value = "\0";

	while ((value_from_datafile[i] >= 48) && (value_from_datafile[i] <= 57))
	{
		tmp_value = tmp_value + to_string(value_from_datafile[i] - 48);
		++i;
	}

	return stoi(tmp_value);
}

//Парсер
void SmartHouseManager::parse_string()
{
	int i = 0;
	int item_number = 0;
	string data_from_file = FW.read_data();
	string tmp_string = "\0";
	while (i < data_from_file.size())
	{
		if ((data_from_file[i] == 'l') && (data_from_file[i + 1] == 'a'))
		{
			i += 5;
			item_number = parse_value(i, data_from_file) - 1;

			if (item_number + 1 > smart_lamps_vec.size())
			{
				exception_out_of_range();
			}
			smart_lamps_vec[item_number].set_item_number(item_number + 1);
			i += 2;
			tmp_string.push_back(data_from_file[i]);
			tmp_string.push_back(data_from_file[i + 1]);
			smart_lamps_vec[item_number].set_location(tmp_string);
			tmp_string = "\0";
			i = data_from_file.find(':', i) + 1;
			while (data_from_file[i] != ';')
			{
				if ((data_from_file[i] == 'B') && (data_from_file[i + 1] == 'R'))
				{
					i += 1 + 2;
					smart_lamps_vec[item_number].set_parameter("BR", parse_value(i, data_from_file));
					i = data_from_file.find(',', i - 1) + 1;
				}
				if (data_from_file[i] == 'R')
				{
					i += 0 + 2;
					smart_lamps_vec[item_number].set_parameter("R", parse_value(i, data_from_file));
					i = data_from_file.find(',', i - 1) + 1;
				}
				if (data_from_file[i] == 'G')
				{
					i += 0 + 2;
					smart_lamps_vec[item_number].set_parameter("G", parse_value(i, data_from_file));
					i = data_from_file.find(',', i - 1) + 1;
				}
				if ((data_from_file[i] == 'B') && (data_from_file[i + 1] != 'R'))
				{
					i += 0 + 2;
					smart_lamps_vec[item_number].set_parameter("B", parse_value(i, data_from_file));
					i = data_from_file.find(';', i - 1);
				}
				else
				{
					i++;
				}

			}
			
		}
		else if ((data_from_file[i] == 'j') && (data_from_file[i + 1] == 'a'))
		{
			i += 9;
			item_number = parse_value(i, data_from_file) - 1;

			if (item_number + 1 > smart_jalousie_vec.size())
			{
				exception_out_of_range();
			}
			smart_jalousie_vec[item_number].set_item_number(item_number + 1);
			i += 2;
			tmp_string.push_back(data_from_file[i]);
			tmp_string.push_back(data_from_file[i + 1]);
			smart_jalousie_vec[item_number].set_location(tmp_string);
			tmp_string = "\0";
			i = data_from_file.find(':', i) + 1;
			while (data_from_file[i] != ';')
			{
				if (data_from_file[i] == 'D')
				{
					i += 2 + 2;
					smart_jalousie_vec[item_number].set_parameter("DEG", parse_value(i, data_from_file));
					i = data_from_file.find(';', i - 1);
				}
				else
				{
					i++;
				}
			}
		}
		++i;
	}
}

//Обсчёт значений датчиков в зависимости от работы умных вещей
void SmartHouseManager::set_sensors_data()
{
	float E = 0, Ia = 0, S = 10;
	float tmp = 0;
	float sun_brightness = SUN.get_parameter("BR");

	int tmp2 = 0;
	float lamp_power_to_lumen_koeff = MAX_LAMP_LUMEN_FLOW / MAX_LAMP_POWER;
	/*Ia - сила света в направлении от источника на заданную точку рабочей поверхности
	  ( определяют по кривым силы света или по таблицам выбранного типа светильника),
	  S-Плоащадь комнаты  */
	LS.set_parameter("OUT", sun_brightness * lamp_power_to_lumen_koeff);
	sun_brightness = 12;



	for (int i = 0; i < smart_lamps_vec.size(); i++)
	{
		Ia += smart_lamps_vec[i].get_parameter("BR");
	}
	Ia = Ia * lamp_power_to_lumen_koeff;
	for (int i = 0; i < smart_jalousie_vec.size(); i++)
	{
		if (smart_jalousie_vec[i].get_parameter("DEG") <= 90)
		{
			tmp2 = smart_jalousie_vec[i].get_parameter("DEG");
		}
		else
		{
			tmp2 = 90 - ((smart_jalousie_vec[i].get_parameter("DEG")) % 90);
		}

		tmp += ((sun_brightness * ((float)tmp2 / 90)) / smart_jalousie_vec.size()) * lamp_power_to_lumen_koeff;
	}
	E = E + Ia + tmp;
	E = E / S;
	LS.set_parameter("LR", E);

}

//Собрать все данные в одну строку
string SmartHouseManager::collect_all_data()
{
	string all_data = "\0";
	all_data += "SUN:" +SUN.get_string()+ ";\n";
	for (int i = 0; i < smart_lamps_vec.size(); i++)
	{
		all_data += "lamp_" +to_string(smart_lamps_vec[i].get_item_number()) +"_"+ smart_lamps_vec[i].get_location() + ":" 
			+ smart_lamps_vec[i].get_string() + ";\n";
	}
	for (int i = 0; i < smart_jalousie_vec.size(); i++)
	{
		all_data += "jalousie_" + to_string(smart_jalousie_vec[i].get_item_number())+"_"+ smart_jalousie_vec[i].get_location() + ":"
			+ smart_jalousie_vec[i].get_string() + ";\n";
	}
	all_data += "li_sensor:" + LS.get_string() + ";\n" + "tm_sensors:" + TS.get_string() + ";\n" + "hm_sensors" + HS.get_string() + ";\n";

	return all_data;
}

//Один цикл программы
void SmartHouseManager::one_cycle()
{
	cout << "time_passed:" << clock() / 1000 << endl;
	SUN.set_parameter("BR", SUN.calculate_brightness());
	parse_string();
	set_sensors_data();
	FW.save_data(collect_all_data());
	Sleep(1000);
}