//3.14153
//3.14161
//3.14167
//3.14151






#include <iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>

using namespace std;

int main()
{ double a,b,c,pi,d;
int i;

   srand(time(NULL));

   for(i=1;i<=100000000;++i){
   a=rand()*2000/(RAND_MAX+1)/1000.000-1;
   b=rand()*2000/(RAND_MAX+1)/1000.000-1;
   c=sqrt(a*a+b*b);
    if(c<=1)d=d+1;

   }
   pi=d/100000000*4;
    cout<<pi;
    return 0;
}
