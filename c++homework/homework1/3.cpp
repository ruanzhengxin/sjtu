#include <iostream>

using namespace std;

int main()
{ int x,a,b,c,d;
  char ch1,ch2,ch3,ch4;
   cin>>x;

   d=x%10;
   c=(x%100-d)/10;
   b=(x%1000-c*10-d)/100;
   a=(x%10000-b*100-c*10-d)/1000;
   ch1=a+12+'A';
   ch2=b+12+'A';
   ch3=c+12+'A';
   ch4=d+12+'A';



    cout << ch1<<ch2<<ch3<<ch4 << endl;
    return 0;
}
