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
        //string filename = "D:\\labs\\ItLab\\ItLab_SmartHouse\\Rozanov\\test\\test.txt";
        
        ifstream fin;
        string lastLine = "";
        string buf;
        fin.open(filename); 
        while (std::getline(fin, buf, '\n'))
        {
            lastLine = buf;
        }

        if (lastLine == "")
        {
            cout << "EMPTY STR";
        }

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