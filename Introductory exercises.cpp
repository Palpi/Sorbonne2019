// my_class.h
#ifndef MY_CLASS_H // include guard
#define MY_CLASS_H

#include <iostream>

using namespace std;

// ex 2.1. 1
// program that verifies if a number is even or odd
bool isEven(int n) {
    if (n % 2 == 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}
// ex 2.1. 2
// program asking for 2 integers and returning their sum, product, difference and division
void basicOperations(){
    int A, B;
    
    cout << "Provide A: ";
    cin >> A;
    cout << "Provide B: ";
    cin >> B;

    cout << "Sum: " << A + B << endl;
    cout << "Difference: " << A - B << endl;
    cout << "Product: " << A * B << endl;
    cout << "Division: " << (float) A / B << endl;

}

// ex 2.1. 3
// program asking for 2 integers A and B, exchanging their values and returning
void swapAB() {
    int A, B, temp;
    
    cout << "Provide A: ";
    cin >> A;
    cout << "Provide B: ";
    cin >> B;

    temp = A;
    A = B;
    B = temp;

    cout << "Now A = " << A << endl;
    cout << "And B = " << B << endl;
}


#endif