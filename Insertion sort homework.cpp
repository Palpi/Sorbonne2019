#include <iostream>
#include <cmath>
#include <ctime>
#include <climits>
#include <cstdlib>

using namespace std;

int main()

{
    int x[5]={4,2,3,1,5}, j=0, temp = 0;

    for (int i = 0; i<4; ++i)
        {

         while (x[i+1]>x[j])
            {
             ++j;
            }

         temp = x[i+1];

         for (int t=i; t>=j; --t)
            {
             x[t+1]=x[t];
            }
         x[j]=temp;

         j=0;

        }

    cout<<"The sorted array is ";
    for (int i =0; i<=4;++i)
    {
        cout<<x[i]<<" ";
    }
    cout<<endl;

    system (" pause "); /* include this at the end so that the program doesn ’t close
before you see the output */

}