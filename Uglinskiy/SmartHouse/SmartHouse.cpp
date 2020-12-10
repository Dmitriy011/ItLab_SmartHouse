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
   
}

