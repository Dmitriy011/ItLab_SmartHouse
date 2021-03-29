#include "Jalousie.h"

Jalousie::Jalousie()
{
    mode_j.push_back(0);
    mode_j.push_back(0);
    mode_j.push_back(0);
    mode_j.push_back(0);
    number_jalousie = 0;
}

int Jalousie::Mode()
{
    ReadFile jalousie;

    jalousie.read_txt();
    number_jalousie = jalousie.Get_number_jalousie();

    switch (number_jalousie)
    {
    case 1:
    {
        mode_j[0] = stoi(jalousie.GetValueJ());
        break;
    }
    case 2:
    {
        mode_j[1] = stoi(jalousie.GetValueJ());;
        break;
    }
    case 3:
    {
        mode_j[2] = stoi(jalousie.GetValueJ());;
        break;
    }
    case 4:
    {
        mode_j[3] = stoi(jalousie.GetValueJ());;
        break;
    }
    }

    return GetMode(number_jalousie);
}

int Jalousie::GetMode(size_t _n) const
{
    return mode_j[_n - 1];
}

/*
int Jalousie::count_closer_jalousie() const
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
*/

size_t Jalousie::Get_number_jalousie() const
{
    return number_jalousie;
}
