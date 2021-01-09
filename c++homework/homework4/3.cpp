#include <iostream>
#define maxsize 1000
using namespace std;
template <class T1,class T2>
void paixu(T1 a[maxsize],T2 n)
{
    int lh,rh,k;
    float tmp;
   for(lh=0;lh<n;lh++){
    rh=lh;
   for(k=lh;k<n;k++)
    if(a[k]<a[rh]) rh=k;
   tmp=a[lh];
   a[lh]=a[rh];
   a[rh]=tmp;}
   for(lh=0;lh<n;++lh)
    cout<<a[lh]<<"   ";

}
int main()
{
   float array[6]={1520.15,15.2,25.253,25.452,3.152,45.256};
   int array1[8]={45,1515,325,48786,21,3,9,99};


    cout<<"排序浮点数组1520.15,15.2,25.253,25.452,3.152,45.256"<<endl;
    paixu<float,int>(array,6);
    cout<<endl;
   cout<<"排序整数组45,1515,325,48786,21,3,9,99"<<endl;

    paixu<int,int>(array1,8);

    return 0;
}
