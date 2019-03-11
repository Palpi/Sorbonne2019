#ifndef LECTURE2_H
#define LECTURE2_H

#include <iostream>

using namespace std;

// ex 2.2. 1 
int max(int arr[], int arrLen){
    int tempMax;

    tempMax = arr[0];

    for (int i=1; i < arrLen; i++)
    {
        if (arr[i] > tempMax)
        {
            tempMax = arr[i];
        }
    }
    return tempMax;
}

long factorial(long n)
{
    return (n ==0 || n==1) ? 1 : factorial(n-1)*n;

}

long Fibonacci(long n)
{
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    else
    {
        return Fibonacci(n - 2) + Fibonacci(n - 1);
    }

}

void meanAndVariance(double arr[], int len)
{
    double sum=0, sumsq=0, mean, var;

    for (int i=0; i < len; i++)
    {
        sum+=arr[i];
        sumsq+=arr[i]*arr[i];
    }

    mean = sum/len;
    var = sumsq/len - (mean*mean);

    cout << "mean: " << mean << endl;
    cout << "variance: " << var << endl;

}

// ex 2.1. 1
// program that verifies if a number is even or odd
bool isEven(int n) {
    return (n % 2 == 1) ? false : true;
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