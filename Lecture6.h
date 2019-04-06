#ifndef LECTURE6_H
#define LECTURE6_H

#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

void probOfDefault() {

    int n, t, accidents;
    double prob, defaults = 0, x, premium, compensation, profit;
    srand((unsigned) time(0));

    cout << "Please provide: " << endl;

    do {
        cout << "Amount of premium [should be positive!]:" << endl;
        cin >> premium;
    } while (premium <= 0);

    do {
        cout << "Amount of compensation [should be positive!]:" << endl;
        cin >> compensation;
    } while (compensation <= 0);

    do {
        cout << "Probability of accident [should be between 0 and 1!]:" << endl;
        cin >> prob;
    } while (prob <= 0 || prob > 1);

    do {
        cout << "Number of clients [should be positive!]:" << endl;
        cin >> n;
    } while (n <= 0);

    do {
        cout << "Number of iterations [should be positive!]:" << endl;
        cin >> t;
    } while (t <= 0);

    for (int i = 0; i < t; i++) {
        accidents = 0;
        for (int j = 0; j < n; j++) {
            x = (double) rand() / RAND_MAX;
            if (x < prob) {
                accidents++;
            }
        }
        profit = n * premium - accidents*compensation;
        if (profit < 0) {
            defaults++;
        }
    }

    defaults /= t;
    cout << "Probability of default is: " << defaults << endl;
    system("pause");
}




#endif
