#include "complex.h"



int main()
{    Complex c1(2,2) ,c2(1,3), c3(2,2),c4;
     c1.display();
     c2.display();
     c3.display();
     c4=c1+c2;
     c4.display();
     c4=c1*c2;
     c4.display();
     if(c1!=c2)cout<<"c1,c2不相等"<<endl;
     if(c1==c3)cout<<"c1,c3相等"<<endl;
    return 0;
}
