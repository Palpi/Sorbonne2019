#include <iostream>
#include "Lecture2.h"

using namespace std;

int main()
{

    // Lecture 2
    cout << "factorial of 5: " << factorial(5) << endl;
    cout << "5. element in Fibonacci sequence: " << Fibonacci(5) << endl;
    cout << "Is 5 even?" << isEven(5) << endl;
    basicOperations();
    swapAB();

    int egArrInt[5] = {45, 12023, 62, 923, -5}; 
    cout << "Max of {45, 12023, 62, 923, -5} is: " << max(egArrInt, 5) << endl;

    double egArrDbl[5] = {45.2, 120, 62.12, 93.3, -5.3}; 
    cout << "Mean and variance of {45.2, 120, 62.12, 93.3, -5.3} are: " << endl;
    meanAndVariance(egArrDbl, 5);
    // end of Lecture 2




system("pause");

}