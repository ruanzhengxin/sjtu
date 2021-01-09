#include <iostream>

using namespace std;

int main()
{  double pi,i=1,a,b=-1,c;
   while(a>0.00001){
       b=(-1)*b;
        pi=1/i*b+pi;
        a=1/i-1/(i+2);
        i=i+2;



   }
   c=4*pi;

    cout << c << endl;
    return 0;
}
