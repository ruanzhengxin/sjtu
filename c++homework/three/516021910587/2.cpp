#include <iostream>

using namespace std;

int main()

{   int a,b,c,d;
    bool flag;
    cin>>a>>b;
    if(a>b)a=a;
      else if (a==b) a=a;
               else {c=a;
                    a=b;
                    b=c;}
    do{
        if(a%b!=0)
        {d=a%b;
        a=b;
        b=d;
        flag=true;}
        else
             flag=false;

        }while(flag);
        cout<<b;



    return 0;
}
