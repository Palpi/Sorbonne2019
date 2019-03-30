#ifndef LECTURE5_H
#define LECTURE5_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

void bubbleSort() {

    int i, j, temp, n=5;

    int arr[n] = {1,7,-5,50,2};

    for (i=0; i<n; i++)
    {
        for (j=0; j<i; j++)
        {
            if (arr[i] < arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    cout << "bubble sorted arr: ";
    for (i=0; i<n; i++){
        cout << arr[i] << ",";
    }


}

#endif
