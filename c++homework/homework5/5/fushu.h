#ifndef FUSHU_H_INCLUDED
#define FUSHU_H_INCLUDED
#include<iostream>
using namespace std;
class fushu{
   double shibu;
   double xubu;
   public:
       void add(const fushu &a1,const fushu &a2);
       void product(const fushu &a1,const fushu &a2);
       double getshibu();
       double getxubu();
       fushu(double a,double b);

};


#endif // FUSHU_H_INCLUDED
