#include <iostream>

using namespace std;

int main()
{  int m=0,n=0,i,j;

   const int maxsize=100;


   cout<<"�������������������"<<endl;
   cin>>m>>n;

   int a[maxsize][maxsize],hangmax[maxsize]={0},liemin[maxsize]={0};


   cout<<"���������"<<endl;
   for(i=0;i<m;++i)
    for(j=0;j<n;++j)
    cin>>a[i][j];

    for(i=0;i<m;++i)
        for(j=0;j<n;++j)
    {
        if(a[i][j]>a[i][hangmax[i]])hangmax[i]=j;
    }
    for(j=0;j<n;++j)
      for(i=0;i<m;++i)
      {
          if(a[i][j]<a[liemin[j]][j])liemin[j]=i;
      }
      for(i=0;i<m;++i)
      {if(i==liemin[hangmax[i]])
      {cout<<"�а���"<<endl;
       cout<<"mat["<<liemin[i]<<"]["<<hangmax[i]<<"]="<<a[liemin[i]][hangmax[i]]<<endl;
       break;}





        else cout<<"no found"<<endl;

      }
    return 0;
}
