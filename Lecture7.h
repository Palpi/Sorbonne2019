#ifndef LECTURE7_H
#define LECTURE7_H

#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<sstream>
#include<limits>
#include<string>
#include <cctype>
#include <iostream>

using namespace std;



void ExampleSimpleValidation(){

    int tempInt, lBound = 0, uBound = 100;

    do 
    {
        cout << "enter an integer within the range " << lBound << " to " << uBound << ": ";
        cin >> tempInt; 
    } while (tempInt < 0 || tempInt > 100);

}

void ExampleCinIgnore(){

    int tempInt, lBound = 0, uBound = 100;
    bool cont;

    cout << "enter an integer within the range " << lBound << " to " << uBound << ": ";
    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> tempInt;

    cout << "it's ok and tempInt is: " << tempInt << endl;

}

void ExampleParseFromString(){

    string initStr, tempStr = ""; 
    int tempInt, lBound = 0, uBound = 100;

    cout << "enter an integer within the range " << lBound << " to " << uBound << ": ";
    cin >> initStr;

    for (char c : initStr) 
    {
        if (isdigit(c)) tempStr += c;
    }

    cout << tempStr << endl; 

    tempInt = (tempStr == "") ? tempInt = 0 : stoi(tempStr);

    cout << "it's ok and tempInt is: " << tempInt << endl;

}

void ExampleTryCatch(){

    int tempInt, lBound = 0, uBound = 100;
    string tempStr;

    // TO TRZEBA DOPRACOWAĆ

    // try
    // {
    //     cout << "enter an integer within the range " << lBound << " to " << uBound << ": ";
    //     cin >> tempStr;

    //     if (tempInt < 0 || tempInt > 100)
    //     {
    //         throw "tempInt is out of bounds!";
    //     }
    // }
    // catch (runtime_error& e)
    // {
    //     cout << "Runtime error" << endl;
    // }
    // catch (exception& e)
    // {
    //     cout << "Exception: " << e.what() << endl;
    // }

}

void LectureSeven()
{
    // ExampleSimpleValidation();
    // ExampleCinIgnore();
    // ExampleParseFromString();
    ExampleTryCatch();
}

#endif
