#include <iostream>

using namespace std;

int main()
{  int  a[13]={0,12,43,71,102,132,163,193,224,255,285,316,346};
   int b[13]={0,12,43,72,103,133,164,194,225,256,286,317,347};
   int i,j,k,n,yi=0,er=0,san=0,si=0,wu=0,liu=0,qi=0;
   cin>>n;
   for(i=1900;i<=1900+n-1;i++)
   {

   if((i%4==0&&i%100!=0)||i%400==0)
    {for(j=1;j<=366;j++)
     for(k=0;k<13;k++)
     if(j==b[k]&&j%7==1)yi+=1;
     if(j==b[k]&&j%7==2)er+=1;
     if(j==b[k]&&j%7==3)san+=1;
     if(j==b[k]&&j%7==4)si+=1;
     if(j==b[k]&&j%7==5)wu+=1;
    if(j==b[k]&&j%7==6)liu+=1;
    if(j==b[k]&&j%7==0)qi+=1; }
    else
     {for(j=1;j<=365;j++)
     for(k=0;k<13;k++)
     if(j==a[k]&&j%7==1)yi+=1;
     if(j==a[k]&&j%7==2)er+=1;
     if(j==a[k]&&j%7==3)san+=1;
     if(j==a[k]&&j%7==4)si+=1;
     if(j==a[k]&&j%7==5)wu+=1;
    if(j==a[k]&&j%7==6)liu+=1;
    if(j==a[k]&&j%7==0)qi+=1; }



   }cout<<yi<<" "<<er<<" "<<san<<" "<<si<<" "<<wu<<" "<<liu<<" "<<qi<<endl;

    return 0;
}
