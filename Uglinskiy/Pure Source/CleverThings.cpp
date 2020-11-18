#include <iostream>
#include "ClassCleverThings.h"
#include <map> 
#include<Windows.h>

using namespace std;


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    LightSensors LS;

    //write_sensors_data_in_file(generate_sensors_data(LS, 3));

    SmartLamp A;
    A.get_string();
    A.parse_string();
    A.set_p_of_li();
    A.print_info();

 // A.parse_string();
    //A.set_degree(30) ;
    //A.print_info();
    //A.set_degree(90.123);
    //A.print_info();
    ////A.generate_one_le(1);
    //A.generate_data(12);
    //cout << A.total_data << endl;
    //A.write_data_in_file();

    /////////////////////////
   /* map<string, string> vocabulary;

    int size = 0, operations = 0;
    cout << "Enter number of words: " ;
    cin >> size;
    cout << endl;

    for(int i=0;i<size;i++)
    {
        string word_en = "\0", word_ru = "\0";

        cout << i << " word\nen: ";
        cin >> word_en;
        cout << "ru: ";
        cin >> word_ru;

        vocabulary.insert(make_pair(word_en, word_ru));
    }

    map<string, string>::iterator it;

    it = vocabulary.begin();
    for (int i = 0; i < size; i++) 
    {
        cout << "Key:" << it->first << " Value: " << it->second << endl;
        it++;
    }

    cout << "Enter number of operations: ";
    cin >> operations;
    cout << "Operations: 1-read   2-insert   3-erase   4-change" << endl;


    for (int i = 0; i < operations ; i++) 
    {
        int curren_operation=0;
        cout << "Enter operation: ";
        cin >> curren_operation;

        if (curren_operation == 1)
        {
            string find_element = "\0";

            cout << "Enter element to read" << endl;
            cin >> find_element;

            it = vocabulary.find(find_element);
            cout << "Key:" << it->first << " Value: " << it->second << endl;
        }

    }*/


}

