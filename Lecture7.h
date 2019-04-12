#ifndef LECTURE7_H
#define LECTURE7_H

#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<sstream>
#include<limits>
#include<string>

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

    try
    {
        cout << "enter an integer within the range " << lBound << " to " << uBound << ": ";
        cin >> tempStr;

        tempInt = stoi(tempStr);

        if (tempInt < 0 || tempInt > 100)
        {
            throw "the number is outside the range!";
        }
    }
    catch (exception& e)
    {
        cout << "Exception: " << e.what() << endl;
    }

    cout << "END" << endl;
}


void SaveToFile() {

    ofstream textFile;
    textFile.open ("output.txt");
    textFile << "The force is strong with you.\n";
    textFile << "A powerful Sith you will become.\n";
    textFile << "Henceforth, you shall be known as Darth...Vader.\n";
    textFile.close();

    char listSeparator=';';

    ofstream csvFile;
    csvFile.open ("output.csv");
    csvFile << "col1"<< listSeparator <<"col2"<< listSeparator <<"col3\n";
    csvFile << "1"<< listSeparator <<"2"<< listSeparator <<"3\n";
    csvFile << "11"<< listSeparator <<"22"<< listSeparator <<"33.\n";
    csvFile.close();

    cout << "Files saved!" << endl;

}


void LectureSeven()
{
    ExampleSimpleValidation();
    ExampleCinIgnore();
    ExampleParseFromString();
    ExampleTryCatch();

    SaveToFile();
}

#endif
