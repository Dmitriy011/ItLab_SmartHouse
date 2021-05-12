#include <iostream>
#include "Smart_House_Manager.h"
#include "py_client.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	

	setenv("PYTHONPATH", "D:\\ITLAB_repos\\ItLab_SmartHouse\\Uglinskiy\\Smart_House", true);
	TSmartHouseManager Manager(12, 4, 4, 4);
	

	Manager.one_cycle();
	return 0;

}