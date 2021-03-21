#include "TTheSun.h"
#include <ctime>

using std::clock;
//расчЄт €ркости солнца в зависимости от лонца
int TTheSun::calculate_brightness()
{
	int day_lenght = 15, half_day_lenght = 0;		//создаЄм переменные продолжительность суток и продолжительность половины суток в секундах	
	int day_time = (clock() / 1000) % (day_lenght);	//создаЄм переменную ,отвечаующую за текущее врем€ суток в секундах
	//оно высчитываетс€ по следующей формуле:ЅерЄтс€ врем€ прошедшее от начала программы в секундах
	//и от него берЄм остаток от делени€ на продолжительность суток
	//Ѕлагодар€ этому добиваемс€ зацикливани€ суток на прот€жении работы программы.ќдин цикл равен day_lenght
	int time_to_night = 0;//переменна€ отвечающа€ за ближайшее количество секунд до 00:00.Ќе может быть больше half_day_lenght
	float sun_brightness_to_daytime_koeff = 0;		//коэффициент отвачающий за то,сколько времени должно пройти чтобы изменить €ркость солнца на 1 у.е.
	half_day_lenght = day_lenght / 2;				//высчитываем половину суток

	if (day_time <= half_day_lenght)//если врем€ меньше полудн€ то просто записываем значение day_time  в  time_to_night
	{
		time_to_night = day_time;
	}
	else//иначе высчитываем сколько времени остаЄтс€ до наступлени€ 00:00
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
	sun_brightness_to_daytime_koeff = (float)half_day_lenght / MAX_LAMP_POWER;
	return (time_to_night / sun_brightness_to_daytime_koeff);//возвращаем €ркость в у.е.
}