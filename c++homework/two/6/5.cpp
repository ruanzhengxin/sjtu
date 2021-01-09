#include <iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
using namespace std;

int main()

{  int n,i,a=0,b=0,c=0,d=0,x,j;
   double s,q;
   cin>>n;
   q=0;
   srand(time(NULL));
   for(i=1;i<=1000000;++i)
   {
       for(j=1;j<=n;++j)
       {x=rand()*4/(RAND_MAX+1);
       switch(x){
      case 0:a=a+1;break;
      case 1:b=b+1;break;
      case 2:c=c+1;break;
      case 3:d=d+1;break;}}


      s=sqrt((a-b)*(a-b)+(c-d)*(c-d));




      q=q+s;
      a=0;
      b=0;
      c=0;
      d=0;


   }
   cout<<q/1000000<<endl;



    return 0;
}
