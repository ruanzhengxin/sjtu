#include "fushu.h"
fushu::fushu(double a,double b)
{
    shibu=a;
    xubu=b;
}
void fushu::add(const fushu &a1,const fushu &a2)
{
    shibu=a1.shibu+a2.shibu;
    xubu=a1.xubu+a2.xubu;
}
void fushu::product(const fushu &a1,const fushu &a2)
{
    shibu=a1.shibu*a2.shibu-a1.xubu*a2.xubu;
    xubu=a1.shibu*a2.xubu+a1.xubu*a2.shibu;
}

double fushu::getshibu()
{
    return shibu;
}
double fushu::getxubu()
{
    return xubu;
}
