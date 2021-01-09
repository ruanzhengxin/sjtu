#include "fushu.h"
void display(fushu q)
{
    if(q.getxubu()<0){cout<<q.getshibu()<<q.getxubu()<<"i"<<endl;}
    if(q.getxubu()==0){cout<<q.getshibu()<<endl;}
    if(q.getxubu()>0){cout<<q.getshibu()<<"+"<<q.getxubu()<<"i"<<endl;}
}

int main()
{    fushu a1(1.2,-3.4);
     fushu a2(3.5,4.1);
     fushu a3(0,0),a4(0,0);
     a3.add(a1,a2);
     a4.product(a1,a2);

     display(a3);

     display(a4);

    return 0;
}
