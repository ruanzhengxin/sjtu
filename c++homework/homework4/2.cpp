#include <iostream>
#define maxsize 10000

using namespace std;
bool flag;
bool isperfectnumber(int x);



int main()
{   int i=0,n=0,m=0;
    cout << "Please input m,n:" << endl;
    cin>>m>>n;
    for(i=m;i<=n;i++)
    {isperfectnumber(i);

    if(flag)cout<<i<<endl;}



    return 0;
}
bool isperfectnumber(int x)
{int j,s=0;
 for(j=x-1;j>1;j--)
 {if(x%j==0)s+=j;}
  s=s+1;

 if(s==x)flag=true;
 else flag=false;

return flag;
 }




