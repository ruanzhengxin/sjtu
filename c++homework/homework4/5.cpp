#include <iostream>
#define maxsize 100
using namespace std;
int chazhao(int a[],int key,int high,int low)
{int mid=0;
    if(low<=high)
    {mid=(low+high)/2;
    if(key==a[mid])return mid;
    else if(key<a[mid]) return chazhao(a,key,mid-1,low);

      else if(key>a[mid])return chazhao(a,key,high,mid+1);}

    else return -1;

}

int main()
{   int array[maxsize]={},i,n,m;
    cout<<"please input length of array"<<endl;
    cin>>m;
    cout<<"please input array"<<endl;
    for(i=0;i<m;i++)
        cin>>array[i];
    cout<<"searching number"<<endl;
       cin>>n;
    cout<<chazhao(array,n,m,1)+1<<endl;
    return 0;
}
