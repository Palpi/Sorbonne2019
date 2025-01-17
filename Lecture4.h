#ifndef LECTURE4_H
#define LECTURE4_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int LCG(int a, int c, int m, int x0)
{
    return (a*x0 + c) % m ;
}


void generateLCG() {

    int a, c, m, x1, x0, n = 1000;
    double mean, stdev, sum=0, sumsq=0, u;


    cout << "This program generates " << n << " pseudorandom numbers using LCG" << endl;
    cout << "Please provide a:" << endl;
    cin >> a;
    cout << "Please provide c:" << endl;
    cin >> c;
    cout << "Please provide m:" << endl;
    cin >> m;
    cout << "Please set a x0:" << endl;
    cin >> x0;

    for (int i = 0; i < n; i++)
    {
        x1 = LCG(a, c, m, x0);
        x0 = x1;

        u = (double)x1/m;
        sum+=u;
        sumsq+=u*u;
    }

    mean = (double)sum/n;
    stdev = (double)sumsq/n - mean*mean;
    stdev = sqrt(stdev);

    cout << "Mean should be equal to: " << 0.5 << endl;
    cout << "And pseudorandom mean is equal to: " << mean << endl; 
    cout << "Standard deviation should be equal to: " << 1/sqrt(12) << endl;
    cout << "And pseudorandom standard deviation is equal to: " << stdev << endl; 

}

void generateRand() {

    int x1, n = 1000;
    double mean, stdev, sum=0, sumsq=0, u;

    srand((unsigned) time(0));

    cout << "This program generates " << n << " pseudorandom numbers using standard C++ pseudorandom generator" << endl;

    for (int i = 0; i < n; i++)
    {
        x1 = rand();

        u = (double)x1/RAND_MAX;
        sum+=u;
        sumsq+=u*u;
    }

    mean = (double)sum/n;
    stdev = (double)sumsq/n - mean*mean;
    stdev = sqrt(stdev);

    cout << "Mean should be equal to: " << 0.5 << endl;
    cout << "And pseudorandom mean is equal to: " << mean << endl; 
    cout << "Standard deviation should be equal to: " << 1/sqrt(12) << endl;
    cout << "And pseudorandom standard deviation is equal to: " << stdev << endl; 

}

void guessRandom() {

    int answer, guess, lBound, uBound;

    cout << "Choose lower bound! " << endl;
    cin >> lBound;
    cout << "Choose upper bound! " << endl;
    cin >> uBound;

    if (uBound <= lBound) {
        cout << "Upper bound should be bigger than lower bound. Run program again." << endl;
        exit(0);
    }

    srand((unsigned) time(0)); // use this to change seed

    answer = lBound + rand() % (uBound - lBound + 1); //this will allow to generate uniform dist on the interval
    guess = uBound + 2;

    while (answer != guess) {
        cout << "Guess a number!" << endl;
        cin >> guess;
        if (answer < guess) {
            cout << "Less" << endl;
        } else if (answer > guess) {
            cout << "More" << endl;
        }
    }
    cout << "Bravo!" << endl;

}

double providePi(long precision) {

    int i;
    double x, y, pi = 0, c;

    srand((unsigned) time(0));

    for (i = 0; i < precision; ++i) {

        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;
        c = x * x + y * y;
        if (c <= 1) {
            pi++;
        }
    }

    pi /= precision;
    pi *= 4;

    return pi;
}

double boxMuller(double pmean, double pvar){

    double x, y, s, z, p;

    do {
        x = ((double) rand() * 2 / RAND_MAX) - 1;
        y = ((double) rand() * 2 / RAND_MAX) - 1;
        s = x * x + y * y;
    } while (s > 1);

    z = x * sqrt(-2 * log(s) / s);
    p = sqrt(pvar) * z + pmean;

    return p;
}


void checkBoxMullerFunction() {

    int i, iter = 10000;
    double p, desiredMean, desiredVar, sum = 0, var = 0;

    srand((unsigned)time(0));

    cout << "Please provide desired mean of parametrised normal distribution: ";
    cin >> desiredMean;
    cout << "Please provide desired variance of parametrised normal distribution: ";
    cin >>  desiredVar;

    for (i = 0; i < iter; ++i) 
    {
        p = boxMuller(desiredMean, desiredVar);
        sum += p;
        var += p * p;
    }

    cout << "Mean is supposed to be: " << desiredMean << endl;
    cout << "..and the sample mean is: " << sum / iter << endl;

    var /= iter;
    var = var - sum * sum / (iter * iter);

    cout << "Variance is supposed to be: " << desiredVar << endl;
    cout << "..and the sample variance is: " << var << endl;

}

#endif
