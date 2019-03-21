#include <iostream>
#include <cmath>
#include <ctime>
#include <climits>
using namespace std;

int main()
{
    double x,y,p=0;
    long n =10000000;

    srand((unsigned) time (0));
    for (int i=1;i<=n;++i)
    {
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;
        if (x * x + y * y <= 1)
        {
            p += 1;
        }
    }

    p=(double)p*4/n;
    cout<<"estimate of pi is "<<p<<endl;

    system (" pause "); /* include this at the end so that the program doesn ’t close
    before you see the output */
}
