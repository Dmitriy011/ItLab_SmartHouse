#include <iostream>
#include<Windows.h>
#include "Smart_house_Manager.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	SmartHouseManager Manager(2,1);
	//Manager.parse_string();
	//cout << Manager.collect_all_data();
	Manager.one_cycle();

	return 0;
   
}

