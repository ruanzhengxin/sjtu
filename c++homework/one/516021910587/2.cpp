#include <iostream>
#include<cmath>

using namespace std;

int main()
{int x1,x2,a,b,c,dlt;
    a=1;
    b=-(1e20+1);
    c=1e20;
    dlt=b*b-4*a*c;
    x1=(-b+sqrt(dlt))/2/a;
    x2=(-b-sqrt(dlt))/2/a;
    cout << x1<<x2 << endl;
    return 0;
}
//½á¹ûx1=1e20 x2=1
