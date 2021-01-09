#include <iostream>

using namespace std;

int main()
{   int a[10],i,j,l,k,temp=0;

   cout<<"请输入10个整数：";
   for(l=0;l<=9;++l)
    cin>>a[l];
    for(i=0;i<=9;++i)
       {temp=a[i];
       for(j=i-1;j>=0;j--)
        if(temp>a[j])break;
        else a[j+1]=a[j];
        a[j+1]=temp; }
        for(k=0;k<=9;++k)
            cout<<a[k]<<endl;

    return 0;
}
