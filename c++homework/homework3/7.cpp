#include <iostream>

using namespace std;

int main()
{  int n,k,i,j;
   cout<<"请输入有几盏灯几个人"<<endl;
   cin>>n>>k;
   int a[n]={0};
   for(i=1;i<=n;++i)
    a[i]=1;
   for(j=2;j<=k;++j)
   {for(i=1;i<=n;++i)
     {if(i%j==0)a[i]=a[i]*(-1);}}
    for(i=1;i<=n;++i)
    if(a[i]==1)cout<<i<<endl;









    return 0;
}
