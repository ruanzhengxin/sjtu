#include <iostream>
#define maxsize 100
using namespace std;

void printint(int a,int b)
{char shuzi[maxsize]={};
int j=0,k,c;

 do
 {c=a%b;
     if(c>=10)shuzi[j]=c-10+'A';
    else shuzi[j]=c+'0';
    a/=b;
    j++;
 }while(a!=0);
for(k=j-1;k>=0;k--)
    cout<<shuzi[k];



}


int main()
{  int i,base,n;

    cout<<"please input n, base:"<<endl;
    cin>>n>>base;
    printint(n,base);


    return 0;
}
