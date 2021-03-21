#pragma once
#include <string>
using std::string;
//Класс Комната
class TRoom
{
private:
	float S = 1;//площадь
	float sun_energy_percentage=1;//коэффициент отвечающий за то ,сколько света(энергии солнца) доходит до комнаты
	string name = "\0";//имя
public:
	TRoom(float Sq = 1,float s_e_p=1,string nm="room")
	{
		S = Sq;
		sun_energy_percentage = s_e_p;
		name = nm;
	}
	//получить площаль
	float get_S()
	{
		return S;
	}
	//получить коэффициент солнечной энергии
	float get_sun_en_per()
	{
		return sun_energy_percentage;
	}
	//получить имя комнаты
	string get_name()
	{
		return name;
	}

	////под вопросом нужны ли сэттеры
	void set_S(float Sq)
	{
		S = Sq;
	}
	void set_sun_en_per(float s_e_p)
	{
		sun_energy_percentage = s_e_p;
	}
};