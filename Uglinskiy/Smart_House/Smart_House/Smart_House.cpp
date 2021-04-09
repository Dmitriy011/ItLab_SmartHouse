#include <iostream>
#include "Smart_House_Manager.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	TSmartHouseManager Manager(4,12,4);

	//while (clock() / 1000 <30)
	//{
	//	Manager.one_cycle();

	//}

	Manager.one_cycle();
	return 0;

}