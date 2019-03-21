#include <iostream>
#include <cmath>
#include <ctime>
#include <climits>
using namespace std;

int main()
{
    double u, v, s, z, mean=0, variance=0;
    int n=10000, m=0;

    srand((unsigned)time(0));
    for (int i=1;i<=n;++i)
        {
        u =(double)rand()/RAND_MAX *2-1;
        v =(double)rand()/RAND_MAX *2-1;
        s=u*u+v*v;
        if (s<1)
            {
            z=u*sqrt(-2*log(s)/s);
            mean+=z;
            variance+=z*z;
            m+=1;
            }
        }

    mean = (double)mean/m;
    variance = (double)variance/m-mean*mean;

    cout<<"mean is "<<mean<<", theoretical mean should be 0"<<endl;
    cout<<"variance is "<<variance<<", theocal variance should be 1"<<endl;

    system (" pause "); /* include this at the end so that the program doesn ’t close
    before you see the output */
}