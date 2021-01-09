#include"account.h"
void savingaccount::creataccount(int a)
{
    account=a+1;
    money=100*(a+1);
}
void savingaccount::salary(double x)
{
    money=money+money*x;
}
void savingaccount::display()
{   cout<<"ÕËºÅ"<<"     "<<"ÕË»§Óà¶î"<<endl;
    cout<<account<<"      "<<money<<endl;
}
