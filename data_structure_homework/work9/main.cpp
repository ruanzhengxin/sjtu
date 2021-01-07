#include <iostream>
#include<string>
#include <stdlib.h>
using namespace std;

int Partition (int *L, int low, int high)
{
    int temp = L[low];
    int pt   = L[low]; //哨兵
    while (low != high)
    {
        while (low < high && L[high] >= pt)
            high--;
        L[low] = L[high];

        while (low < high && L[low] <= pt)
            low++;
        L[high] = L[low];
    }
    L[low] = temp;
    return low;
}

void QSort (int *L, int low, int high)  //快速排序
{
    int pl;
    if (low < high)
    {
        pl = Partition (L,low,high);
        QSort (L, low,  pl-1);
        QSort (L, pl+1, high);
    }
}

void findk(int k,int *L,int low,int high)
{
    int temp;
    temp=Partition(L,low,high);
    if(temp==k-1)
    {
        cout<<L[temp]<<endl;return;
    }
    else if(temp>k-1)
        findk(k,L,low,temp-1);
    else
        findk(k,L,temp+1,high);
}
int main()
{   string s1,s2;
    getline(cin,s1);
    getline(cin,s2);
    int length=0;
    int target=0;
    int i=0;
    int a=0;
    while(i<s1.length())
    {
        if(s1[i]!=' '){i++;}
        else {a=i;i++;}
    }
    length=atoi(s1.substr(0,a).c_str());
    target=atoi(s1.substr(a,s1.length()).c_str());
    i=0;
    int m=0;
    int *c=new int[length];
    a=0;
    s2+=" ";
    while(i<s2.length())
    {
        if(s2[i]!=' '){i++;}
        else {c[a]=atoi(s2.substr(m,i).c_str());i++;a++;m=i;}
    }


    findk(length-target+1,c,0,length-1);
    //cout<<length<<target;
    return 0;
}
