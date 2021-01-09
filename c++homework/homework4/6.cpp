#include <iostream>
#define maxsize 100
using namespace std;
void shengchengxinjihe(int a[],int n)
{
    int i,j;

    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
        if(a[i]==a[j])a[j]=0;
    for(i=0;i<n;i++)
        if(a[i]==0)continue;
        else cout<<a[i]<<"  ";
}
void tianjiayuansu(int a[],int n)
{   int num=0,i;
    for(i=0;i<maxsize;i++)
     if(a[i])num++;
    a[num]=n;
    for(i=0;i<=num;i++)
        cout<<a[i]<<"  ";
  }
bool chazhaoyuansu(int a[],int n)
 {
     bool flag;
     int i;
     for(i=0;i<maxsize;i++)
        if(a[i]==n){flag=true;break;}
     else flag=false;
     return flag;

 }
void qiujiaoji(int a[],int b[])
{

    int i,j,k,num1,num2;
    for(i=0;i<maxsize;i++)
     if(a[i])num1++;
     for(i=0;i<maxsize;i++)
     if(b[i])num2++;

        for(j=0;j<7;j++)
          for(k=0;k<7;k++)
     if(a[j]==b[k]){cout<<a[j]<<"  ";continue;}

}
void qiubingji(int a[],int b[])
{
  int i,j,k,*p,num3=0,num4=0;
    for(i=0;i<maxsize;i++)
     if(a[i])num3++;
     for(i=0;i<maxsize;i++)
     if(b[i])num4++;
    p=new int [num3+num4];
    for(j=0;j<num3;j++)
        p[j]=a[j];
    for(j=num3;j<num3+num4;j++)
      {

      k=j-num3;
        p[j]=b[k]; }
    shengchengxinjihe(p,num3+num4);
}
int main()
{   int array1[10]={1,2,2,3,14,15,16,16,16,20};
    int array2[maxsize]={1,2,3,14,15,16,20};
    int array3[maxsize]={1,2,3,14,15,16,20};
    int array4[maxsize]={12,22,3,142,15,16,202};
    int array5[maxsize]={1,2,3,14,15,16,20};
    cout<<"数组1,2,2,3,14,15,16,16,16,20"<<endl;
    cout<<"生成集合";
    shengchengxinjihe(array1,10);
    cout<<endl;
    cout<<"数组1,2,3,14,15,16,20添加元素30"<<endl;
    tianjiayuansu(array2,30);
    cout<<endl;
    cout<<"数组1,2,3,14,15,16,20"<<endl;
    cout<<"查找14"<<endl;
    if(chazhaoyuansu(array3,14))cout<<"存在"<<endl;
    else cout<<"不存在"<<endl;
    cout<<"查找21"<<endl;
    if(chazhaoyuansu(array3,21))cout<<"存在"<<endl;
    else cout<<"不存在"<<endl;
    cout<<"取集合1,2,3,14,15,16,20和集合12,22,3,142,15,16,202的交集"<<endl;
    qiujiaoji(array2,array4);
    cout<<endl;
    cout<<"取集合1,2,3,14,15,16,20和集合12,22,3,142,15,16,202的并集"<<endl;
    qiubingji(array5,array4);




    return 0;
}
