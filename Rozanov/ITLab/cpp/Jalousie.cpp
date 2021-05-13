#include "Jalousie.h"

Jalousie::Jalousie()
{
    mode_j.push_back(0);
    mode_j.push_back(0);
    mode_j.push_back(0);
    mode_j.push_back(0);
}

int Jalousie::init_mode_jalousie(size_t number_jalousie, int value)
{
    switch (number_jalousie)
    {
    case 1:
    {
        mode_j[0] = value;
        break;
    }
    case 2:
    {
        mode_j[1] = value;
        break;
    }
    case 3:
    {
        mode_j[2] = value;
        break;
    }
    case 4:
    {
        mode_j[3] = value;
        break;
    }
    }

    return GetMode(number_jalousie);
}

int Jalousie::Get_count_closer_jalousie() const
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        if (mode_j[i] == 0)
        {
            count++;
        }
    }

    return count;
}

int Jalousie::GetMode(size_t _n) const
{
    return mode_j[_n - 1];
}
