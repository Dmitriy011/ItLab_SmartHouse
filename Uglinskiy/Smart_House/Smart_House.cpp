#include <iostream>
#include "Smart_House_Manager.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	TSmartHouseManager Manager(4,12,4,0);

	//while (clock() / 1000 <30)
	//{
	//	Manager.one_cycle();

	//}
	TSmartLamp Temp_SL;
	TSmartBattery temp_SB;
	TSmartJalousie temp_SJ;
	
	/*Manager.insert_smart_lamp(Temp_SL,"SR");
	Manager.insert_smart_battery(temp_SB,"BT");
	Manager.insert_smart_jalousie(temp_SJ,"LR");*/
	Manager.one_cycle();
	return 0;

}