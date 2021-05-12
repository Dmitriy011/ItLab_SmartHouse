#pragma once
#include <string>
using std::string;
//Класс Комната
class TRoom
{
private:
	float S = 1;//площадь
	float t = 0;
	float medium_vapor_content = 12;//среднее содержание влаги 
	string name = "\0";//имя
public:
	TRoom(float Sq = 1, float s_e_p = 1, string nm = "room")
	{
		S = Sq;
		
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
	//среднее содержание влаги 
	float get_med_vapor_content()
	{
		return medium_vapor_content;
	}
	//температура
	float get_t()
	{
		return t;
	}
	/*---Setters---*/
	//температура
	void set_t(float set_t = 1)
	{
		t = set_t;
	}
	//среднее содержание влаги 
	void set_med_vapor_content(float new_content)
	{
		medium_vapor_content = new_content;
	}
};