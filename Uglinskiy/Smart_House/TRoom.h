#pragma once
#include <string>
using std::string;
//Класс Комната
class TRoom
{
private:
	float S = 1;//площадь
	float t = 0;
	float sun_energy_percentage = 1;//коэффициент отвечающий за то ,сколько света(энергии солнца) доходит до комнаты
	string name = "\0";//имя
public:
	TRoom(float Sq = 1, float s_e_p = 1, string nm = "room")
	{
		S = Sq;
		sun_energy_percentage = s_e_p;
		name = nm;
	}
	/*---Getters---*/
	//имя комнаты
	string get_name()
	{
		return name;
	}
	//площаль
	float get_S()
	{
		return S;
	}
	//коэффициент солнечной энергии
	float get_sun_en_per()
	{
		return sun_energy_percentage;
	}
	//температура
	float get_t()
	{
		return t;
	}
	/*---Setters---*/
	void set_t(float set_t = 1)
	{
		t = set_t;
	}

};