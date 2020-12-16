#include <iostream>
#include<Windows.h>
#include "Smart_house_Manager.h"
#define _CRT_SECURE_NO_WARNINGS

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	SmartHouseManager Manager;
	Manager.one_cycle();
	//SmartLamp SL;
	//SL.set_parameter("lamp_1", "G", 1241452);
	//SL.set_parameter("lamp_2", "G", 12452);
	//cout<<"lamp_1:" <<SL.get_parameter("lamp_1", "G")<<"\nlamp_2:"<< SL.get_parameter("lamp_2", "G");
	//cout <<"\nget_string:\n"<< SL.get_string() << endl;	
	//cout << "\n\nlamp_1:" << SL.get_parameter("lamp_1", "G") << "\nlamp_2:" << SL.get_parameter("lamp_2", "G");
	//cout << "\nget_string:\n" << SL.get_string() << endl;
	
	/*SmartLamp Lamp;
	Lamp.set_parameter("lamp_1", "B", 200);
	cout << Lamp.get_parameter("lamp_1", "B")<<endl;
	cout << Lamp.get_string()<< endl;
	SmartJalousie SJ;

	SJ.set_parameter("jalousie_1", "DEG", 90);
	cout << SJ.get_parameter("jalousie_1", "DEG") << endl;
	cout << SJ.get_string() << endl;

	LightSensors LS;
	HumiditySensors HS;
	TemperatureSensors TS;
	cout << LS.current_data_to_string() << HS.current_data_to_string() << TS.current_data_to_string();*/
	return 0;
   
}

