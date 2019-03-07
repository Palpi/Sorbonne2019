#include <iostream>

using namespace std;

// ex 2.2. 1 
int max(int arr[]){
    int tempMax, arrLen;

    arrLen = sizeof(arr)/sizeof(int);
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

void meanAndVariance(double arr[])
{
    int n; 
    double sum=0, sumsq=0, mean, var;

    n = sizeof(arr)/sizeof(double);

    for (int i=0; i < n; i++)
    {
        sum+=arr[i];
        sumsq+=arr[i]*arr[i];
    }

    mean = sum/n;
    var = sumsq/n - (mean*mean);

    cout << "mean: " << mean << endl;
    cout << "variance: " << var << endl;

}


