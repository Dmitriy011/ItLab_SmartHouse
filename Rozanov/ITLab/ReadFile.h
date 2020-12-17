#pragma once

#include <fstream> 
#include <sstream> 

using namespace std;

class ReadTxt
{
public:
	void read()
	{
        string filename = "..\\Uglinskiy\\SmartHouse\\smart_lamp.txt";
        //string filename = "../test/test.txt";
        ifstream fin;
        fin.open(filename);
        if (fin.is_open())
        {
            fin.seekg(-1, ios_base::end);

            bool tmp = true;
            while (tmp)
            {
                char ch;
                fin.get(ch);

                if ((int)fin.tellg() <= 1)
                {
                    fin.seekg(0);
                    tmp = false;
                }
                else
                {
                    if (ch == '\n')
                    {
                        tmp = false;
                    }
                    else
                    {
                        fin.seekg(-2, ios_base::cur);
                    }
                }

            }
        }
        string lastLine;
        getline(fin, lastLine);

        /*
        if (lastLine.find_last_of(';') == 18)
        {
            value.push_back(lastLine[16]);
            value.push_back(lastLine[17]);
        }
        if (lastLine.find_last_of(';') == 17)
        {
            value.push_back(lastLine[16]);
        }
        */

        if (lastLine.find_last_of(';') == 12)
        {
            value.push_back(lastLine[10]);
            value.push_back(lastLine[11]);
        }
        if (lastLine.find_last_of(';') == 11)
        {
            value.push_back(lastLine[10]);
        }
	}

    string GetValue()
    {
        return value;
    }

private:
    string value;
};