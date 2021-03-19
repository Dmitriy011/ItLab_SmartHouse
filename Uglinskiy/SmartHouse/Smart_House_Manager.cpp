#include "Smart_House_Manager.h"


//������� ��� ��������� ������ � ������ � ���� "����"="��������",
string TSensors::get_string()
{

	string tmp_string = "\0";		//������ ������ ������
	map<string, int>::iterator it;	//������ ��������

	it = sensors.begin();			//������������� �������� � ������

	while (it != sensors.end())//����: ���� �� ��������� ����� ����
	{
		tmp_string += it->first + "=" + to_string(it->second) + ',';//��������� � ������� ������: "���� = �������� �����,"
		++it;
		if (it == sensors.end())//������� ��������� �������� �������
		{
			tmp_string.erase(tmp_string.size() - 1);//����� ��������,�� �������� �� ����� 
		}
	}
	return tmp_string;//���������� ���������� ������
}

//������� ��� ��������� ������ � ������ � ���� "����"="��������",
string TSmartLight::get_string()
{
	string return_string = "\0";	//������ ������ ������

	map<string, int>::iterator it;	//������ �������� 
	it = smart_thing_char.begin();	//������������� �������� � ������ ����

	while (it != smart_thing_char.end())//����: ���� �� ��������� ����� ����
	{
		return_string += it->first + "=" + to_string(it->second) + ',';//��������� � ������� ������: "���� = �������� �����,"
		++it;
		if (it == smart_thing_char.end())//������� ��������� �������� �������
		{
			return_string.erase(return_string.size() - 1);//����� ��������,�� �������� �� ����� 
		}
	}
	return return_string;
}

//������ ������� ������ � ����������� �� �����
int TTheSun::calculate_brightness()
{
	int day_lenght = 15, half_day_lenght = 0;		//������ ���������� ����������������� ����� � ����������������� �������� ����� � ��������	
	int day_time = (clock() / 1000) % (day_lenght);	//������ ���������� ,����������� �� ������� ����� ����� � ��������
	//��� ������������� �� ��������� �������:������ ����� ��������� �� ������ ��������� � ��������
	//� �� ���� ���� ������� �� ������� �� ����������������� �����
	//��������� ����� ���������� ������������ ����� �� ���������� ������ ���������.���� ���� ����� day_lenght
	int time_to_night = 0;//���������� ���������� �� ��������� ���������� ������ �� 00:00.�� ����� ���� ������ half_day_lenght
	float sun_brightness_to_daytime_koeff = 0;		//����������� ���������� �� ��,������� ������� ������ ������ ����� �������� ������� ������ �� 1 �.�.
	half_day_lenght = day_lenght / 2;				//����������� �������� �����

	if (day_time <= half_day_lenght)//���� ����� ������ ������� �� ������ ���������� �������� day_time  �  time_to_night
	{
		time_to_night = day_time;
	}
	else//����� ����������� ������� ������� ������� �� ����������� 00:00
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
	return (time_to_night / sun_brightness_to_daytime_koeff);//���������� ������� � �.�.
}

//�������� ������ �� ����� � ������� �� � ���� ������
string TServerInfoFileWorker::read_data()
{
	ifstream in("smart_lamp.txt", ios::in); // �������� ���� ��� ������

	std::stringstream sstr;
	sstr << in.rdbuf();
	return sstr.str();
}

//��������� ������ � ����
void TServerInfoFileWorker::save_data(string string_to_file)
{
	time_t now = time(NULL);//������ ��������� �������

	ofstream in_file("Total_sensors_data.txt");
	if (in_file.is_open())
	{

		in_file << asctime(localtime(&now));//���������� ������� �����
		cout << asctime(localtime(&now));
		in_file << string_to_file << endl;	//���������� ������ �� �������� ������ � ����

		cout << string_to_file << endl;
	}
	in_file.close();//��������� ����
}

//������:���������� ������ �������� � ������� ������ ��� ���������� ����� �����
void TSmartHouseManager::exception_out_of_range()
{
	cout << "ERROR: the number of smart things received from the server is greater than it really exists : the program is closing" << "\n";
	exit(1);
	
}

//������������� ������ ���� � �����,�������� (string)"123"->(int)123
int TSmartHouseManager::parse_value(int start_index, string value_from_datafile)
{
	int i = start_index;//������ �������� �������
	string tmp_value = "\0";
	
	while ((value_from_datafile[i] >= 48) && (value_from_datafile[i] <= 57))//���� ������� ������ �������� ������
	{
		tmp_value = tmp_value + to_string(value_from_datafile[i] - 48);		//����������� ����� � ������ � ���������� � tmp_value
		++i;
	}

	return stoi(tmp_value);//���������� ���������� ������ ��������������� � int 
}

//������
void TSmartHouseManager::parse_string()
{
	int i = 0;
	int item_number = 0;					//��������� ����� ���� 

	string data_from_file = FW.read_data();	//������ ������ �� �����
	string tmp_string = "\0";				//��������� ������ 

	while (i < data_from_file.size())//���� �� ������ ���� ����
	{
		if ((data_from_file[i] == 'l') && (data_from_file[i + 1] == 'a'))//���� ������� ������ ���� 'l' � ��������� 'a'
		{
			i += 5;//������������ � ������ ���� 
			item_number = parse_value(i, data_from_file) - 1;//������������ ����� ���� � �������� �� ���� 1,��� ����������� ���������� ���������

			if (item_number + 1 > smart_lamps_vec.size())
			{
				exception_out_of_range();
			}
			smart_lamps_vec[item_number].set_item_number(item_number + 1);// �������� �������(����� ����) ����� �������� � ������� item_number,� ���� number ���������� item_number+1
			
			i += 2;//������������ � �������������� �������
			//���������� �� ��������� ������ ������������� �������
			tmp_string.push_back(data_from_file[i]);
			tmp_string.push_back(data_from_file[i + 1]);
			smart_lamps_vec[item_number].set_location(tmp_string);//���������� � ���� location tmp_string
			tmp_string = "\0";//�������� ��������� ������
			i = data_from_file.find(':', i) + 1;//������������ � ��������������� ����� ����
			
			while (data_from_file[i] != ';')//���� �� ����� �� ';',�.�. �� ����� ������(������������� ����� ����)
			{
				//��������� ����� �������������� ��������
				if ((data_from_file[i] == 'B') && (data_from_file[i + 1] == 'R'))
				{
					i += 1 + 2;//����������� �� �������� ���� ��������������
					smart_lamps_vec[item_number].set_parameter("BR", parse_value(i, data_from_file));//������������ �����->������������ ��� � ���� 
					i = data_from_file.find(',', i - 1) + 1;//������������ �� ��� ����� �� ','
					//��� ��������� ������� ����������
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
		++i;//��� ������ ������ ������ �� ';' ������������ ������� �� \n,� ����� �� ��������� ������
	}
}

//������ �������� �������� � ����������� �� ������ ����� �����
void TSmartHouseManager::set_sensors_data()
{
	float E = 0, Ia = 0, S = 10,sun_ep=1;	//E-������� �������,Ia-��������� ������� ��������,S-�������,sun_ep-����������� ��������� �������
	float tmp = 0;			//��������� ����������,���������� �� ��,������� ������� �� ������ �������,����� ����������� ����� ������ ������� � �������
	float sun_brightness = 12;				//������� ������
	string tmp_name = "\0";					//��������� ��� �������

	//��������� �������. ����� ��� ���� ����� ����������� �������������� ��� ���������� �������
	vector<TSmartLamp> temp_slamp_vec;		//��������� ������ ��������.
	vector<TSmartJalousie> temp_jal_vec;	//��������� ������ ������
	int tmp2 = 0;							//��������������� ��������� ��� ������� tmp
	float lamp_power_to_lumen_koeff = MAX_LAMP_LUMEN_FLOW / MAX_LAMP_POWER;//����������� ����������,�� ������� ������� �������� � �.� � ������

	//sun_brightness = SUN.get_parameter("BR");
	LS.set_parameter("OUT", sun_brightness * lamp_power_to_lumen_koeff);
	
	//� ����� ����������� �������������� ��� ������ �������
	for (int i = 0; i < rooms_vec.size(); i++) 
	{
		//���������� ������ ������� ������� �� ��������� ����������
		S=rooms_vec[i].get_S();
		sun_ep = rooms_vec[i].get_sun_en_per();
		tmp_name = rooms_vec[i].get_name();
		
		//��������� ��������� ������ ��������
		for (int j = 0; j < smart_lamps_vec.size(); j++)
		{
			//���� �������� ��������� � ������� ������� ��������� � � ������
			if (smart_lamps_vec[j].get_location()== tmp_name)
			{
				temp_slamp_vec.push_back(smart_lamps_vec[j]);
			}
		}
		//�� �� ����� ��� ������� ������
		for (int j = 0; j < smart_jalousie_vec.size(); j++)
		{
			if (smart_jalousie_vec[j].get_location() == tmp_name)
			{
				temp_jal_vec.push_back(smart_jalousie_vec[j]);
			}
		}

		
		//��� ����������� ������� �������� ������������ ��������� �� �������������� ������
		for (int k = 0; k < temp_slamp_vec.size(); k++)
		{
			Ia += temp_slamp_vec[k].get_parameter("BR");
		}

		Ia = Ia * lamp_power_to_lumen_koeff;//��������� ���������� �.�. � ������

		//����������� ��������� ������ ������ ������ � �������
		for (int i = 0; i < temp_jal_vec.size(); i++)
		{
			//����������� �� ������� �������� ������� ������ .���������� �������� �� ����� ���� ������ 90 ��������
			if (temp_jal_vec[i].get_parameter("DEG") <= 90)
			{
				tmp2 = temp_jal_vec[i].get_parameter("DEG");
			}
			else
			{
				tmp2 = 90 - ((temp_jal_vec[i].get_parameter("DEG")) % 90);
			}
			//������� ������� � �������:������� ������*(�� ������� ������� ������ � ���������)/��������� ������*(����������� ��������  ������)
			tmp += ((sun_brightness * ((float)tmp2 / 90)) / temp_jal_vec.size()) * lamp_power_to_lumen_koeff;
		}
		E = E + Ia + tmp;				//���������� ������� ������ � ��������
		E = E / S;						//����������� ������� ������������
		LS.set_parameter(tmp_name, E);	//���������� ���������� �������� � ��������������� ������ �����
		//�������� ��� ��������� ��������������
		temp_slamp_vec.clear();
		temp_jal_vec.clear();
		Ia = 0;
		E = 0;
		tmp = 0; 
		tmp2 = 0;
	}
}

//������� ��� ������ � ���� ������
string TSmartHouseManager::collect_all_data()
{
	string all_data = "\0";						//������ ������ ���� ����� ����������
	all_data += "SUN:" +SUN.get_string()+ ";\n";//���������� ���������� � ������

	//� ����� �������� ��� ����� ����
	for (int i = 0; i < smart_lamps_vec.size(); i++)
	{
		//���������� lamp_(����� �������)_(����������������):(��� �������������� �������);\n
		all_data += "lamp_" +to_string(smart_lamps_vec[i].get_item_number()) +"_"+ smart_lamps_vec[i].get_location() + ":" 
			+ smart_lamps_vec[i].get_string() + ";\n";
	}
	for (int i = 0; i < smart_jalousie_vec.size(); i++)
	{
		all_data += "jalousie_" + to_string(smart_jalousie_vec[i].get_item_number())+"_"+ smart_jalousie_vec[i].get_location() + ":"
			+ smart_jalousie_vec[i].get_string() + ";\n";
	}
	//���������� ������ � �������� li_sensor:(��������� � �������� �����);\n � �.�. ��� ���� ��������
	all_data += "li_sensor:" + LS.get_string() + ";\n" + "tm_sensors:" + TS.get_string() + ";\n" + "hm_sensors" + HS.get_string() + ";\n";

	return all_data;//���������� ���������� ������
}

//���� ���� ���������
void TSmartHouseManager::one_cycle()
{
	cout << "time_passed:" << clock() / 1000 << endl;	//������� ������� ������� � �������� ������ �� ����� ���������
	SUN.set_parameter("BR", SUN.calculate_brightness());//����������� ������� ������ � ���������� ���������� �������� � ��������������� ���� ������
	parse_string();										//������ ������
	set_sensors_data();									//������������� �������� �������� 
	FW.save_data(collect_all_data());					//�������� ��� ������ � ������ � ���������� � ����
	Sleep(1000);										//��� �� 1 ������� 
}