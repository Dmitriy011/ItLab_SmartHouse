#include "Smart_House_Manager.h"


//собрать все имеющиеся данные в строку в виде "ключ"="значение",
string TSensors::get_string()
{

	string tmp_string = "\0";		//создаём пустую строку
	map<string, int>::iterator it;	//создаём итератор

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

//собрать все имеющиеся данные в строку в виде "ключ"="значение",
string TSmartLight::get_string()
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

//расчёт яркости солнца в зависимости от лонца
int TTheSun::calculate_brightness()
{
	int day_lenght = 15, half_day_lenght = 0;		//создаём переменные продолжительность суток и продолжительность половины суток в секундах	
	int day_time = (clock() / 1000) % (day_lenght);	//создаём переменную ,отвечаующую за текущее время суток в секундах
	//оно высчитывается по следующей формуле:Берётся время прошедшее от начала программы в секундах
	//и от него берём остаток от деления на продолжительность суток
	//Благодаря этому добиваемся зацикливания суток на протяжении работы программы.Один цикл равен day_lenght
	int time_to_night = 0;//переменная отвечающая за ближайшее количество секунд до 00:00.Не может быть больше half_day_lenght
	float sun_brightness_to_daytime_koeff = 0;		//коэффициент отвачающий за то,сколько времени должно пройти чтобы изменить яркость солнца на 1 у.е.
	half_day_lenght = day_lenght / 2;				//высчитываем половину суток

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

//Ошибка:количество данных принятых с сервера больше чем количество умных вещей
void TSmartHouseManager::exception_out_of_range()
{
	cout << "ERROR: the number of smart things received from the server is greater than it really exists : the program is closing" << "\n";
	exit(1);
	
}

//Распарсивание строки цифр в число,например (string)"123"->(int)123
int TSmartHouseManager::parse_value(int start_index, string value_from_datafile)
{
	int i = start_index;//откуда начинать парсить
	string tmp_value = "\0";
	
	while ((value_from_datafile[i] >= 48) && (value_from_datafile[i] <= 57))//пока текущий символ является цифрой
	{
		tmp_value = tmp_value + to_string(value_from_datafile[i] - 48);		//преобразуем число в строку и записываем в tmp_value
		++i;
	}

	return stoi(tmp_value);//возвращаем полученную строку преобразованную в int 
}

//Парсер
void TSmartHouseManager::parse_string()
{
	int i = 0;
	int item_number = 0;					//временный номер вещи 

	string data_from_file = FW.read_data();	//читаем данные из файла
	string tmp_string = "\0";				//временная строка 

	while (i < data_from_file.size())//пока не пройдём весь файл
	{
		if ((data_from_file[i] == 'l') && (data_from_file[i + 1] == 'a'))//если текущий символ есть 'l' а следующий 'a'
		{
			i += 5;//перемещаемся к номеру вещи 
			item_number = parse_value(i, data_from_file) - 1;//распарсиваем номер вещи и отнимаем от него 1,для корректного управления векторами

			if (item_number + 1 > smart_lamps_vec.size())
			{
				exception_out_of_range();
			}
			smart_lamps_vec[item_number].set_item_number(item_number + 1);// элементу вектора(умной вещи) номер которого в векторе item_number,в поле number записываем item_number+1
			
			i += 2;//перемещаемся к идентификатору комнаты
			//записываем во временную строку идентификатор комнаты
			tmp_string.push_back(data_from_file[i]);
			tmp_string.push_back(data_from_file[i + 1]);
			smart_lamps_vec[item_number].set_location(tmp_string);//записываем в поле location tmp_string
			tmp_string = "\0";//зануляем временную строку
			i = data_from_file.find(':', i) + 1;//перемещаемся к характеристикам умной вещи
			
			while (data_from_file[i] != ';')//пока не дойдём то ';',т.е. до конца строки(характеристик умной вещи)
			{
				//Проверяем какую характеристику изменять
				if ((data_from_file[i] == 'B') && (data_from_file[i + 1] == 'R'))
				{
					i += 1 + 2;//перемещаеся на значение этой характеристики
					smart_lamps_vec[item_number].set_parameter("BR", parse_value(i, data_from_file));//распарсиваем число->устанвливаем его в поле 
					i = data_from_file.find(',', i - 1) + 1;//перемещаемся за это число на ','
					//Для остальных случаев аналогично
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
		++i;//как только прошли строку до ';' перемещаемся сначала на \n,а затем на следующую строку
	}
}

//Обсчёт значений датчиков в зависимости от работы умных вещей
void TSmartHouseManager::set_sensors_data()
{
	float E = 0, Ia = 0, S = 10,sun_ep=1;	//E-средняя яркость,Ia-суммарная яркость лампочек,S-площадь,sun_ep-коэффициент солнечной энергии
	float tmp = 0;			//временная переменная,отвечающая за то,сколько яркости от солнца остаётся,после прохождения через жалюзи остаётся в комнате
	float sun_brightness = 12;				//яркость солнца
	string tmp_name = "\0";					//временное имя комнаты

	//временные векторы. Нужен для того чтобы расчитывать характеристики для конкретной комнаты
	vector<TSmartLamp> temp_slamp_vec;		//временный вектор лампочек.
	vector<TSmartJalousie> temp_jal_vec;	//временный вектор жалюзи
	int tmp2 = 0;							//вспомогательная перменная для расчёта tmp
	float lamp_power_to_lumen_koeff = MAX_LAMP_LUMEN_FLOW / MAX_LAMP_POWER;//коэффициент отвечающий,за перевод яркости лампочки в у.е в Люмены

	//sun_brightness = SUN.get_parameter("BR");
	LS.set_parameter("OUT", sun_brightness * lamp_power_to_lumen_koeff);
	
	//В цикле высчитываем характеристики для каждой комнаты
	for (int i = 0; i < rooms_vec.size(); i++) 
	{
		//записываем данные текущей комнаты во временные переменные
		S=rooms_vec[i].get_S();
		sun_ep = rooms_vec[i].get_sun_en_per();
		tmp_name = rooms_vec[i].get_name();
		
		//Заполняем временный вектор лампочек
		for (int j = 0; j < smart_lamps_vec.size(); j++)
		{
			//Если лампочка находится в текущей комнате добавляем её в вектор
			if (smart_lamps_vec[j].get_location()== tmp_name)
			{
				temp_slamp_vec.push_back(smart_lamps_vec[j]);
			}
		}
		//То же самое для вектора жалюзи
		for (int j = 0; j < smart_jalousie_vec.size(); j++)
		{
			if (smart_jalousie_vec[j].get_location() == tmp_name)
			{
				temp_jal_vec.push_back(smart_jalousie_vec[j]);
			}
		}

		
		//Для полученного вектора лампочек ввысчитываем суммарную их вырабатываемую яркоть
		for (int k = 0; k < temp_slamp_vec.size(); k++)
		{
			Ia += temp_slamp_vec[k].get_parameter("BR");
		}

		Ia = Ia * lamp_power_to_lumen_koeff;//переводим полученные у.е. в Люмены

		//Высчитываем насколько сильно светит солнце в комнате
		for (int i = 0; i < temp_jal_vec.size(); i++)
		{
			//высчитываем на сколько градусов открыто жалюзи .Полученное значение не может быть больше 90 градусов
			if (temp_jal_vec[i].get_parameter("DEG") <= 90)
			{
				tmp2 = temp_jal_vec[i].get_parameter("DEG");
			}
			else
			{
				tmp2 = 90 - ((temp_jal_vec[i].get_parameter("DEG")) % 90);
			}
			//считаем яркость в Люменах:Яркость солнца*(на сколько открыто жалюзи в процентах)/количеств жалюзи*(коэффициент перевожа  люмены)
			tmp += ((sun_brightness * ((float)tmp2 / 90)) / temp_jal_vec.size()) * lamp_power_to_lumen_koeff;
		}
		E = E + Ia + tmp;				//складываем яркость солнца и лампочек
		E = E / S;						//высчитываем среднюю освещённость
		LS.set_parameter(tmp_name, E);	//записываем полученное значение в соответствующий датчик света
		//зануляем все временные характеристики
		temp_slamp_vec.clear();
		temp_jal_vec.clear();
		Ia = 0;
		E = 0;
		tmp = 0; 
		tmp2 = 0;
	}
}

//Собрать все данные в одну строку
string TSmartHouseManager::collect_all_data()
{
	string all_data = "\0";						//создаём строку куда будем записывать
	all_data += "SUN:" +SUN.get_string()+ ";\n";//Записываем информацию о солнце

	//в цикле проходим все умные вещи
	for (int i = 0; i < smart_lamps_vec.size(); i++)
	{
		//записываем lamp_(номер объекта)_(местонахлождение):(все характеристики объекта);\n
		all_data += "lamp_" +to_string(smart_lamps_vec[i].get_item_number()) +"_"+ smart_lamps_vec[i].get_location() + ":" 
			+ smart_lamps_vec[i].get_string() + ";\n";
	}
	for (int i = 0; i < smart_jalousie_vec.size(); i++)
	{
		all_data += "jalousie_" + to_string(smart_jalousie_vec[i].get_item_number())+"_"+ smart_jalousie_vec[i].get_location() + ":"
			+ smart_jalousie_vec[i].get_string() + ";\n";
	}
	//записываем данные с датчиков li_sensor:(вседанные с датчиков света);\n и т.д. для всех датчиков
	all_data += "li_sensor:" + LS.get_string() + ";\n" + "tm_sensors:" + TS.get_string() + ";\n" + "hm_sensors" + HS.get_string() + ";\n";

	return all_data;//возвращаем полученную строку
}

//Один цикл программы
void TSmartHouseManager::one_cycle()
{
	cout << "time_passed:" << clock() / 1000 << endl;	//выводим сколько времени в секундах прошло от начла программы
	SUN.set_parameter("BR", SUN.calculate_brightness());//расчитываем яркость солнца и записываем полученное значение в соответствующее поле солнца
	parse_string();										//парсим строку
	set_sensors_data();									//устанавливаем значение сенсоров 
	FW.save_data(collect_all_data());					//собираем все данные в строку и записываем в файл
	Sleep(1000);										//сон на 1 секунду 
}