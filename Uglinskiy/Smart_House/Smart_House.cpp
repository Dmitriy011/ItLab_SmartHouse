#include <iostream>
#include "Smart_House_Manager.h"
#include "py_client.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	setenv("PYTHONPATH", "D:\\ITLAB_repos\\ItLab_SmartHouse_Uglinskiy_db\\ItLab_SmartHouse\\Uglinskiy\\Smart_House", true);
	TSmartHouseManager Manager(12, 4, 4, 4);

	//while (clock() / 1000 <30)
	//{
	//	Manager.one_cycle();

	//}

	

	Manager.one_cycle();
	return 0;

}