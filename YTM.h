#include<iostream>
#include<cmath>

using namespace std;

double f(double c, double d, double FV, double PV, int N, double r) {
    double temp;
    temp = (c/r)*pow(1+r, 1-d);
    temp += (FV-c/r)/pow(1+r,N+d);
    temp -= PV;
    return temp;
}

double approximateYTM(double c, double d, double FV, double PV, int N){
    return (c + (FV-PV)/(N+d))/(0.5*(FV+PV));
}

double YTM(){
    double c,d,FV,PV,r,k,rNext, temp;
    int N;

    //PROVIDING VALUES
    double BondPresentValue, faceValue, couponYearlyRate,timeToMaturity,periodsPerYear;

    cout << "Please provide:" << endl;
    cout << "Bond Present Value:"; cin >> BondPresentValue;
    cout << "Face Value:"; cin >> faceValue;
    cout << "Coupon Yearly Rate in percentage terms, i.e. 5.5 means 5.5%:"; cin >> couponYearlyRate;
    cout << "Time To Maturity in years:"; cin >> timeToMaturity;
    cout << "Periods Per Year:"; cin >> periodsPerYear;

    FV = faceValue;
    PV = BondPresentValue;
    k = periodsPerYear;
    c = 0.01 * couponYearlyRate * FV /k;
    N = (int)floor(timeToMaturity*k);
    d = (timeToMaturity - N/k) * k;

    cout << "c: " << c << endl;
    cout << "N: " << N << endl;
    cout << "d: " << d << endl;

    // GRID SEARCH
    double ftemp, tempYTM, tempMin=1;

    for (double r=0.0000001; r < 1; r+=0.0000001)
    {
        ftemp = abs(f(c,d,FV,PV, N, r));
        
        if (ftemp <= tempMin) 
        {
            tempMin = ftemp;
            tempYTM = r;
        }
    }
            cout << "GRID SEARCH: " << endl;
            cout << "f is equal to: " << tempMin << endl;
            cout << "YTM is equal to:" << tempYTM << endl;

    // BINARY SEARCH

    double ubound = 1, lbound = 0;

    do {
        r = lbound + (ubound - lbound)/2;
        ftemp = f(c,d,FV,PV, N, r);

        if (ftemp < 0)
        {
            ubound = r;
        } 
        else
        {
            lbound = r;
        }

    } while (abs(ubound-lbound) > 0.001);

            cout << "BINARY SEARCH: " << endl;
            cout << "f is equal to: " << ftemp << endl;
            cout << "YTM is equal to:" << r << endl;    

    return r;

}