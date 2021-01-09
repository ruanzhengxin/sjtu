#include"complex.h"
#include"longlongint.h"



int main()
{   char *a,*b,*c,*d;
   a="111";
   b="15";
   c="78";
   d="448";
    Complex c1(a,b),c2(c,d);
    cout<<c1+c2<<endl;
    return 0;
}
