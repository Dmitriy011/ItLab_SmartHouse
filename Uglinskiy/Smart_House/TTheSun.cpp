#include "TTheSun.h"
#include <ctime>

using std::clock;
//расчёт яркости солнца в зависимости от лонца
int TTheSun::calculate_brightness()
{
	int day_lenght = 30, half_day_lenght = 0;		//создаём переменные продолжительность суток и продолжительность половины суток в секундах	
	int day_time = (clock() / 1000) % (day_lenght);	//создаём переменную ,отвечаующую за текущее время суток в секундах
	//оно высчитывается по следующей формуле:Берётся время прошедшее от начала программы в секундах
	//и от него берём остаток от деления на продолжительность суток
	//Благодаря этому добиваемся зацикливания суток на протяжении работы программы.Один цикл равен day_lenght
	int time_to_night = 0;//переменная отвечающая за ближайшее количество секунд до 00:00.Не может быть больше half_day_lenght
	float sun_brightness_to_daytime_koeff = 0;		//коэффициент отвачающий за то,на сколько измениться яркость за 1 секундку 
	half_day_lenght = day_lenght / 2;				//высчитываем половину суток

	if (day_time <= half_day_lenght)//если время меньше полудня то просто записываем значение day_time  в  time_to_night
	{
		time_to_night = day_time;
	}
	else//иначе высчитываем сколько времени остаётся до наступления 00:00
	{
		if (day_time != 0)
		{
			time_to_night = day_lenght - day_time;
		}
		else
		{
			time_to_night = 0;
		}
	}
	sun_brightness_to_daytime_koeff = 4*(float)MAX_LAMP_POWER  / half_day_lenght;// [у.е/сек]
	return (time_to_night * sun_brightness_to_daytime_koeff);//возвращаем яркость в у.е.
}