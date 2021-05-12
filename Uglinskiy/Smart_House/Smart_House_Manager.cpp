#include "Smart_House_Manager.h"
/*
void TSmartHouseManager::parse_string()
void TSmartHouseManager::set_sensors_data()
string TSmartHouseManager::collect_all_data()
void TSmartHouseManager::one_cycle()
*/


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
void TSmartHouseManager::read_db()
{
	for (int i = 0,j=0; i < 3; i++,j++)
	{
		string tmp_str= "kitchen/lamp" + to_string(i + 1);
		
		smart_lamps_vec[j].set_location("kitchen");
		smart_lamps_vec[j].set_parameter("power", lamp_select(tmp_str.c_str()));
		cout << "power is " << smart_lamps_vec[j].get_parameter("power")<<endl;

	}
	for (int i = 0,j = 3; i < 3; i++, j++)
	{
		string tmp_str = "bath/lamp" + to_string(i + 1);
		smart_lamps_vec[j].set_location("bath");
		smart_lamps_vec[j].set_parameter("power", lamp_select(tmp_str.c_str()));
		cout << "power is " << smart_lamps_vec[j].get_parameter("power") << endl;

	}
	for (int i = 0,j=6; i < 3; i++, j++)
	{
		string tmp_str = "bed/lamp" + to_string(i + 1);

		smart_lamps_vec[j].set_location("bed");
		smart_lamps_vec[j].set_parameter("power", lamp_select(tmp_str.c_str()));
		cout << "power is " << smart_lamps_vec[j].get_parameter("power") << endl;

	}
	for (int i = 0,j=9; i < 3; i++, j++)
	{
		string tmp_str = "living/lamp" + to_string(i + 1);

		smart_lamps_vec[j].set_location("living");
		smart_lamps_vec[j].set_parameter("power", lamp_select(tmp_str.c_str()));
		cout << "power is " << smart_lamps_vec[j].get_parameter("power") << endl;
	}

	smart_jalousie_vec[0].set_location("kitchen");
	smart_jalousie_vec[0].set_parameter("rotation",jalousie_select("kitchen/jalousie"));
	cout << "rotation is " << smart_jalousie_vec[0].get_parameter("rotation") << endl;
	smart_jalousie_vec[1].set_location("bath");
	smart_jalousie_vec[1].set_parameter("rotation", jalousie_select("bath/jalousie"));
	cout << "rotation is " << smart_jalousie_vec[1].get_parameter("rotation") << endl;
	smart_jalousie_vec[2].set_location("bed");
	smart_jalousie_vec[2].set_parameter("rotation", jalousie_select("bed/jalousie"));
	cout << "rotation is " << smart_jalousie_vec[2].get_parameter("rotation") << endl;
	smart_jalousie_vec[3].set_location("living");
	smart_jalousie_vec[3].set_parameter("rotation", jalousie_select("living/jalousie"));
	cout << "rotation is " << smart_jalousie_vec[3].get_parameter("rotation") << endl;
	

	smart_battery_vec[0].set_location("kitchen");
	smart_battery_vec[0].set_parameter("power",heater_select("kitchen/heater"));
	cout << "power is " << smart_battery_vec[0].get_parameter("power") << endl;	
	smart_battery_vec[1].set_location("bath");
	smart_battery_vec[1].set_parameter("power", heater_select("bath/heater"));
	cout << "power is " << smart_battery_vec[1].get_parameter("power") << endl;
	smart_battery_vec[2].set_location("bed");
	smart_battery_vec[2].set_parameter("power", heater_select ("bed/heater"));
	cout << "power is " << smart_battery_vec[2].get_parameter("power") << endl;
	smart_battery_vec[3].set_location("living");
	smart_battery_vec[3].set_parameter("power", heater_select("living/heater"));
	cout << "power is " << smart_battery_vec[3].get_parameter("power") << endl;


	smart_humidifier_vec[0].set_location("kitchen");
	smart_humidifier_vec[0].set_parameter("power", humidifier_select("kitchen/humidifier"));
	cout << "power is " << smart_humidifier_vec[0].get_parameter("power") << endl;
	smart_humidifier_vec[1].set_location("bath");
	smart_humidifier_vec[1].set_parameter("power", humidifier_select("bath/humidifier"));
	cout << "power is " << smart_humidifier_vec[1].get_parameter("power") << endl;
	smart_humidifier_vec[2].set_location("bed");
	smart_humidifier_vec[2].set_parameter("power", humidifier_select("bed/humidifier"));
	cout << "power is " << smart_humidifier_vec[2].get_parameter("power") << endl;
	smart_humidifier_vec[3].set_location("living");
	smart_humidifier_vec[3].set_parameter("power", humidifier_select("living/humidifier"));
	cout << "power is " << smart_humidifier_vec[3].get_parameter("power") << endl;
	
}

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

			if (item_number + 1 < 10)
			{
				i += 2;
			}
			else if (item_number + 1 >= 10)
			{
				i += 3;
			}
			//перемещаемся к идентификатору комнаты
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
					smart_lamps_vec[item_number].set_parameter("power", parse_value(i, data_from_file));//распарсиваем число->устанвливаем его в поле 
					i = data_from_file.find(';', i - 1);//перемещаемся за это число на ','
					//Для остальных случаев аналогично
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
					smart_jalousie_vec[item_number].set_parameter("rotation", parse_value(i, data_from_file));
					i = data_from_file.find(';', i - 1);
				}
				else
				{
					i++;
				}
			}
		}
		else if ((data_from_file[i] == 'b') && (data_from_file[i + 1] == 'a'))
		{
			i += 8;
			item_number = parse_value(i, data_from_file) - 1;

			if (item_number + 1 > smart_battery_vec.size())
			{
				exception_out_of_range();
			}

			i += 2;
			tmp_string.push_back(data_from_file[i]);
			tmp_string.push_back(data_from_file[i + 1]);
			smart_battery_vec[item_number].set_location(tmp_string);
			tmp_string = "\0";
			i = data_from_file.find(':', i) + 1;

			while (data_from_file[i] != ';')
			{
				if (data_from_file[i] == 'p')
				{
					i += 4 + 2;
					smart_battery_vec[item_number].set_parameter("power", parse_value(i, data_from_file));
					i = data_from_file.find(';', i - 1);
				}
				else
				{
					i++;
				}
			}

		}
		else if (data_from_file[i] == 'h')
		{
			i += 11;
			item_number = parse_value(i, data_from_file) - 1;

			if (item_number + 1 > smart_humidifier_vec.size())
			{
				exception_out_of_range();
			}

			i += 2;
			tmp_string.push_back(data_from_file[i]);
			tmp_string.push_back(data_from_file[i + 1]);
			smart_humidifier_vec[item_number].set_location(tmp_string);
			tmp_string = "\0";
			i = data_from_file.find(':', i) + 1;

			while (data_from_file[i] != ';')
			{
				if (data_from_file[i] == 'p')
				{
					i += 4 + 2;
					smart_humidifier_vec[item_number].set_parameter("power", parse_value(i, data_from_file));
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
	for (int i = 0; i < smart_lamps_vec.size(); i++)
	{
		string loc = smart_lamps_vec[i].get_location();
		if (loc == "BT")
		{
			loc = "bath";
		}
		else if (loc == "KN")
		{
			loc = "kitchen";
		}
		else if (loc == "SR")
		{
			loc = "bed";
		}
		else if (loc == "LR")
		{
			loc = "living";
		}
		smart_lamps_vec[i].set_location(loc);
		
	}
	for (int i = 0; i < smart_jalousie_vec.size(); i++)
	{
		string loc = smart_jalousie_vec[i].get_location();
		if (loc == "BT")
		{
			loc = "bath";
		}
		else if (loc == "KN")
		{
			loc = "kitchen";
		}
		else if (loc == "SR")
		{
			loc = "bed";
		}
		else if (loc == "LR")
		{
			loc = "living";
		}
		smart_jalousie_vec[i].set_location(loc);
	}
	for (int i = 0; i < smart_battery_vec.size(); i++)
	{
		//записываем lamp_(номер объекта)_(местонахлождение):(все характеристики объекта);\n
		string loc = smart_battery_vec[i].get_location();
		if (loc == "BT")
		{
			loc = "bath";
		}
		else if (loc == "KN")
		{
			loc = "kitchen";
		}
		else if (loc == "SR")
		{
			loc = "bed";
		}
		else if (loc == "LR")
		{
			loc = "living";
		}
		smart_battery_vec[i].set_location(loc);
	}
	for (int i = 0; i < smart_humidifier_vec.size(); i++)
	{
		//записываем lamp_(номер объекта)_(местонахлождение):(все характеристики объекта);\n
		string loc = smart_humidifier_vec[i].get_location();
		if (loc == "BT")
		{
			loc = "bath";
		}
		else if (loc == "KN")
		{
			loc = "kitchen";
		}
		else if (loc == "SR")
		{
			loc = "bed";
		}
		else if (loc == "LR")
		{
			loc = "living";
		}
		smart_humidifier_vec[i].set_location(loc);
	}
}
//Обсчёт значений датчиков в зависимости от работы умных вещей
void TSmartHouseManager::set_sensors_data()
{					
	float lamp_power_to_lumen_koeff = MAX_LAMP_LUMEN_FLOW / MAX_LAMP_POWER;//коэффициент отвечающий,за перевод яркости лампочки в у.е в Люмены
	float t_out =(float)TS.get_parameter("OUT");//температура снаружи
	float sun_brightness = 43;//яркость солнца
	//sun_brightness = SUN.get_parameter("BR");
	sun_brightness = SUN.get_parameter("power");
	LS.set_parameter("OUT", sun_brightness * lamp_power_to_lumen_koeff);
	sensor_insert("sun", LS.get_parameter("OUT"));
	//В цикле высчитываем характеристики для каждой комнаты
	for (int i = 0; i < rooms_vec.size(); i++) 
	{
		float E = 0, Ia = 0, S = 10, t = 0, bat_power = 0, p = 0, abs_humi = 0;;
		//E-средняя яркость,Ia-суммарная яркость лампочек,S-площадь,sun_ep-коэффициент солнечной энергии,t-температура,
	    //bat_power - суммарная мощность батареи,optimal_power -оптимальная сумарная вырабатыаемая мощность  в комнате,
		float tmp = 0, tmp2 = 0;//tmp - временная переменная,отвечающая за то,сколько яркости от солнца остаётся,
								//после прохождения через жалюзи.tmp2 -временная переменная для расчёта tmp

		string tmp_name = "\0";	//временное имя комнаты

		//временные векторы. Нужен для того чтобы расчитывать характеристики для конкретной комнаты
		vector<TSmartLamp>	     temp_lamp_vec;		//временный вектор лампочек.
		vector<TSmartJalousie>	  temp_jal_vec;	//временный вектор жалюзи
		vector<TSmartBattery>     temp_bat_vec;
		vector<TSmartHumidifier> temp_humi_vec;
		float medium_power = 0;//средняя мощность на квадратный метр
		//записываем данные текущей комнаты во временные переменные
		S=rooms_vec[i].get_S();
		tmp_name = rooms_vec[i].get_name();
		//Заполняем временный вектор лампочек
		for (int j = 0; j < smart_lamps_vec.size(); j++)
		{
			//Если лампочка находится в текущей комнате добавляем её в вектор
			if (smart_lamps_vec[j].get_location()== tmp_name)
			{
				temp_lamp_vec.push_back(smart_lamps_vec[j]);
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
		//для батареи
		for (int j = 0; j < smart_battery_vec.size(); j++)
		{
			if (smart_battery_vec[j].get_location() == tmp_name)
			{
				temp_bat_vec.push_back(smart_battery_vec[j]);
			}
		}
		for (int j = 0; j < smart_humidifier_vec.size(); j++)
		{
			if (smart_humidifier_vec[j].get_location() == tmp_name)
			{
				temp_humi_vec.push_back(smart_humidifier_vec[j]);
			}
		}

	
	//--------------------Освещённость------------------//
		//Для полученного вектора лампочек высчитываем суммарную их вырабатываемую яркоть
		for (int k = 0; k < temp_lamp_vec.size(); k++)
		{
			Ia += temp_lamp_vec[k].get_parameter("power");
		}

		Ia = Ia * lamp_power_to_lumen_koeff;//переводим полученные у.е. в Люмены

		//Высчитываем насколько сильно светит солнце в комнате
		for (int i = 0; i < temp_jal_vec.size(); i++)
		{
			//высчитываем на сколько градусов открыто жалюзи .Полученное значение не может быть больше 90 градусов
			if (temp_jal_vec[i].get_parameter("rotation") <= 90)
			{
				tmp2 = temp_jal_vec[i].get_parameter("rotation");
			}
			else
			{
				
				tmp2 = 90 - ((temp_jal_vec[i].get_parameter("rotation")) % 90);
			}
			//считаем яркость в Люменах:Яркость солнца*(на сколько открыто жалюзи в процентах)/количеств жалюзи*(коэффициент перевожа  люмены)
			tmp += (sun_brightness * (tmp2 / 90))  * lamp_power_to_lumen_koeff;
		}
		if (temp_jal_vec.size() == 0)
		{
			tmp = sun_brightness * lamp_power_to_lumen_koeff;
		}
		E = E + Ia + tmp;				//складываем яркость солнца и лампочек
		E = E / S;						//высчитываем среднюю освещённость
		LS.set_parameter(tmp_name, E);	//записываем полученное значение в соответствующий датчик света
		sensor_insert((tmp_name + "/brightness").c_str(),LS.get_parameter(tmp_name));

		//---------Температура--------------//
		for (int j = 0; j < temp_bat_vec.size(); j++)
		{
			bat_power += ((float)temp_bat_vec[j].get_parameter("power")/100)*ONE_BATTERY_MAX_POWER;
		}
		medium_power = (float)bat_power / S;

		t = t_out +(float)31 * medium_power / 50;
		//cout << "optimal_power:" << optimal_power << " bat_power:" << bat_power << " medium_power:" << medium_power << endl;
		TS.set_parameter(tmp_name, t+0.5);
		sensor_insert((tmp_name + "/temperature").c_str(), TS.get_parameter(tmp_name));

		//-------------Влажность---------------//
/*
Aбсолютная влажность a — масса водяного пара в граммах в 1 м3 влажного воздуха. Измеряется в г/м3.
Вычислить можно по формуле a= 217⋅e/T [г/м3], T — температура воздуха [°K].
*/
		float current_humidifier_power = 0;
		if (temp_humi_vec.size() > 0)
		{
			current_humidifier_power =(float)temp_humi_vec[0].get_parameter("power") / 100;
		}
		float e = 0;
		e = 6.112 * exp(17.62 * t / (243.12 + t));
		abs_humi =( 217*e/((float)t + 273.f) );//г/м^3
		//abs_humi = 217.0f * (std::exp(1)) /(	(float)(TS.get_parameter(tmp_name))+273.15f	);
		rooms_vec[i].set_med_vapor_content(rooms_vec[i].get_med_vapor_content() +
			(current_humidifier_power)*MAX_HUMDIFIER_PERFORMANCE / ((float)60*S*2.6));//устанавливаем новое среднее содержание водяного пара в воздухе
			//	p_new=p_old+((power/100)*(MAX_HUMDIFIER_PERFORMANCE/60))/S					  //к текущему прибавляем количество выброшенное увлажнителем
		p = ((float)rooms_vec[i].get_med_vapor_content() / abs_humi)*100;
	
		if (p>100)
		{
			p = 100;
		}
		HS.set_parameter(tmp_name, p);
		sensor_insert((tmp_name + "/humidity").c_str(), HS.get_parameter(tmp_name));
	}
}


			/*----динамическое добавление вещей----*/

//лампочка
void TSmartHouseManager::insert_smart_lamp(TSmartLamp lamp_to_ins, string where_to_ins)
{
	lamp_to_ins.set_item_number(smart_lamps_vec.size() + 1);
	lamp_to_ins.set_location(where_to_ins);

	smart_lamps_vec.push_back(lamp_to_ins);

	SUN.set_item_number(smart_lamps_vec.size() + 1);

}

//жалюзи
void TSmartHouseManager::insert_smart_jalousie(TSmartJalousie jal_to_ins, string where_to_ins)
{
	jal_to_ins.set_item_number(smart_jalousie_vec.size() + 1);
	jal_to_ins.set_location(where_to_ins);

	smart_jalousie_vec.push_back(jal_to_ins);
}

//баттареи
void TSmartHouseManager::insert_smart_battery(TSmartBattery batt_to_ins, string where_to_ins)
{
	batt_to_ins.set_item_number(smart_battery_vec.size() + 1);
	batt_to_ins.set_location(where_to_ins);

	smart_battery_vec.push_back(batt_to_ins);
}
//Собрать все данные в одну строку

string TSmartHouseManager::collect_all_data()
{
	string all_data = "\0";						//создаём строку куда будем записывать


	//в цикле проходим все умные вещи
	for (int i = 0; i < smart_lamps_vec.size(); i++)
	{
		//записываем lamp_(номер объекта)_(местонахлождение):(все характеристики объекта);\n
		all_data += "lamp_" + to_string(i%3+1) + "_" + smart_lamps_vec[i].get_location() + ":"
			+ smart_lamps_vec[i].get_string() + ";\n";
	}
	all_data += "sun:" + SUN.get_string() + ";\n";//Записываем информацию о солнце
	for (int i = 0; i < smart_jalousie_vec.size(); i++)
	{
		all_data += "jalousie_" + smart_jalousie_vec[i].get_location() + ":"
			+ smart_jalousie_vec[i].get_string() + ";\n";
	}
	for (int i = 0; i < smart_battery_vec.size(); i++)
	{
		//записываем lamp_(номер объекта)_(местонахлождение):(все характеристики объекта);\n
		all_data += "battery_" + smart_battery_vec[i].get_location() + ":"
			+ smart_battery_vec[i].get_string() + ";\n";
	}
	//записываем данные с датчиков li_sensor:(вседанные с датчиков света);\n и т.д. для всех датчиков
	for (int i = 0; i < smart_humidifier_vec.size(); i++)
	{
		//записываем lamp_(номер объекта)_(местонахлождение):(все характеристики объекта);\n
		all_data += "humidifier_" + smart_humidifier_vec[i].get_location() + ":"
			+ smart_humidifier_vec[i].get_string() + ";\n";
	}
	all_data += "li_sensor:" + LS.get_string() + ";\n" + "tm_sensors:" + TS.get_string() + ";\n" + "hm_sensors:" + HS.get_string() + ";\n";

	cout << all_data<<endl;
	return all_data;//возвращаем полученную строку
}
//Один цикл программы
//(один цикл = 1 минута)
void TSmartHouseManager::one_cycle()
{
	cout << "time_passed:" << clock() / 1000 << endl;	//выводим сколько времени в секундах прошло от начла программы
	SUN.set_parameter("power", SUN.calculate_brightness());//расчитываем яркость солнца и записываем полученное значение в соответствующее поле солнца
	cout <<"power" <<SUN.get_parameter("power")<<endl;
	read_db();										//парсим строку
	set_sensors_data();		
	collect_all_data();//устанавливаем значение сенсоров 

	

	parse_string();
	set_sensors_data();	
	FW.save_data(collect_all_data());	//собираем все данные в строку и записываем в файл
	Sleep(1000);										//сон на 1 секунду 
}
