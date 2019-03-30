#ifndef LECTURE3_H
#define LECTURE3_H

#include <iostream>
#include <cmath>
#include "Lecture2.h"

using namespace std;

// 3.1 Exercises
// Program answering the question whether the number is prime or not

bool isPrime(int n)
{
    int  restFromDivision = 1, testDivisor = 2;
    
    while (testDivisor <=sqrt(n) && restFromDivision != 0) 
    { 
        restFromDivision = n % testDivisor;
        ++testDivisor;
    }

    return restFromDivision == 0 ? false : true; 
}

void quadraticEquation()
{
    double a, b, c, delta;
    cout << "This program is calculating real roots of a quadratic equation ax^2 + bx + c = 0!" << endl;
    cout << "Please provide a: ";
    cin >> a;
    cout << "Please provide b: ";
    cin >> b;
    cout << "Please provide c: ";
    cin >> c;

    delta = b*b - 4*a*c;

    if (delta > 0)
    {
        double x1, x2;
        x1 = (-b + sqrt(delta))/(2*a);
        x2 = (-b - sqrt(delta))/(2*a);
        cout << "There are two roots: " << x1 << ", " << x2 << endl;
    } else if (delta == 0){
        double x;
        x = -b/(2*a);
        cout << "There is one root: " << x << endl;
    } else {
        cout << "There are no real roots of this equation." << endl;
    }
}

void HeronFormula()
{
    double a, b, c;
    cout << "This program is calculating area of a triangle using Heron's formula, i.e., providing only length of each side a triangle (a,b,c)" << endl;
    cout << "Please provide a: ";
    cin >> a;
    cout << "Please provide b: ";
    cin >> b;
    cout << "Please provide c: ";
    cin >> c;

    if (a > b + c || b > a + c || c > a + b)
    {
        cout << "this is not a proper triangle. the longest side cannot be longer than the sum of two other sides." << endl;
    }
    else
    {
        double s = 0.5*(a+b+c);
        cout << "Area of this triangle is equal to: " << sqrt(s*(s-a)*(s-b)*(s-c)) << endl;
    }
}



#endif
