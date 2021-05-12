#include "Smart_House_Manager.h"

//чтение из базы
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


//Обсчёт значений датчиков в зависимости от работы умных вещей
void TSmartHouseManager::set_sensors_data()
{					
	float lamp_power_to_lumen_koeff = MAX_LAMP_LUMEN_FLOW / MAX_LAMP_POWER;//коэффициент отвечающий,за перевод яркости лампочки в у.е в Люмены
	//температура снаружи
	float sun_brightness = 44;//яркость солнца
	//sun_brightness = SUN.get_parameter("BR");
	sun_brightness = SUN.get_parameter("power");
	LS.set_parameter("OUT", sun_brightness * lamp_power_to_lumen_koeff);
	sensor_insert("sun", LS.get_parameter("OUT"));

	float t_out = (float)TS.get_parameter("OUT");
	sensor_insert("out/temperature", t_out);

	//В цикле высчитываем характеристики для каждой комнаты
	for (int i = 0; i < rooms_vec.size(); i++) 
	{
		float E = 0, Ia = 0, S = 10, t = 0, bat_power = 0,medium_power = 0, p = 0, abs_humi = 0;
		//E-средняя яркость,Ia-суммарная яркость лампочек,S-площадь,t-температура,
	    //bat_power - суммарная мощность батареи,medium_power -средняя мощность на квадратный метр,p-относительная влажность,abs_humi-абсолютная предельная влажность
		
		float tmp = 0, tmp2 = 0;//tmp - временная переменная,отвечающая за то,сколько яркости от солнца остаётся,
								//после прохождения через жалюзи.tmp2 -временная переменная для расчёта tmp

		string tmp_name = "\0";	//временное имя комнаты

		//временные векторы. Нужен для того чтобы расчитывать характеристики для конкретной комнаты
		vector<TSmartLamp>	     temp_lamp_vec;		//временный вектор лампочек.
		vector<TSmartJalousie>	  temp_jal_vec;	//временный вектор жалюзи
		vector<TSmartBattery>     temp_bat_vec;
		vector<TSmartHumidifier> temp_humi_vec;
		
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
			bat_power += (float)temp_bat_vec[j].get_parameter("power");
		}
		if (tmp_name == "living")
		{
			bat_power = bat_power * 1.9;
		}
		if (tmp_name == "bed")
		{
			bat_power = bat_power * 1.1;
		}
		if (tmp_name == "bath")
		{
			bat_power = bat_power *0.60;
		}
		if (tmp_name == "kitchen")
		{
			bat_power = bat_power * 0.85;
		}
	
		medium_power = bat_power / S+(100*t_out+3380)/62;//100x−62y+3380=0
		if ((bat_power<200)&&(t_out<-20))
		{
			medium_power = medium_power * 5;
		}
		cout <<" bat = "<< bat_power << " p = " << p<< "  med = " << medium_power << endl;
		t = 22*medium_power/100;

		//cout << "optimal_power:" << optimal_power << " bat_power:" << bat_power << " medium_power:" << medium_power << endl;
		TS.set_parameter(tmp_name, t+0.5);
		sensor_insert((tmp_name + "/temperature").c_str(), TS.get_parameter(tmp_name));

		//-------------Влажность---------------//
/*
Предельная абсолютная влажность abs_humi — масса водяного пара в граммах в 1 м3 влажного воздуха. Измеряется в г/м3.
Вычислить можно по формуле abs_humi= 217⋅e/T [г/м3], T — температура воздуха [°K].
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
	SUN.set_parameter("power", 3);//расчитываем яркость солнца и записываем полученное значение в соответствующее поле солнца
	cout <<"power" <<SUN.get_parameter("power")<<endl;
	read_db();										//парсим строку
	set_sensors_data();		
	collect_all_data();//устанавливаем значение сенсоров 
}
