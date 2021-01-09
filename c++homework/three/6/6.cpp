#include <iostream>

using namespace std;

int main()
{  int m=0,n=0,i,j;
   const int maxsize=100;
   bool flag=true;

   cout<<"请输入矩阵行数和列数"<<endl;
   cin>>m>>n;

   int a[maxsize][maxsize],hangmax[maxsize]={0},liemin[maxsize]={0};

   cout<<"请输入矩阵"<<endl;
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
       flag=true;

      else flag=false;
     }cout<<flag<<endl;
     if(flag){ cout<<"有鞍点"<<endl;
         cout<<"mat["<<liemin[i]<<"]["<<hangmax[i]<<"]"<<endl;}
         else cout<<"not found"<<endl;

    return 0;
}
