#include "account.h"



int main()
{    cout<<"ÊäÈëÀûÂÊ"<<endl;
     double x;
    cin>>x;

    savingaccount a[10];
    int i;
    for(i=0;i<10;i++)
      a[i].creataccount(i);
    for(i=0;i<10;i++)
      a[i].salary(x);
    for(i=0;i<10;i++)
      a[i].display();
    return 0;
}
