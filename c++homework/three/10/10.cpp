#include <iostream>
#include<cstring>

using namespace std;

int main()
{  char ch[10][80];
   int i,j,n,e[10]={},shuzi=0,zimu=0,qita=0;
   cout<<"please input the number of lines"<<endl;
   cin>>n;
   for(i=0;i<=n;i++)
    cin.getline(ch[i],80);
    for(i=0;i<=n;i++)
        e[i]=strlen(ch[i]);
    for(i=0;i<=n;i++)
        for(j=0;j<=e[i];j++)
        {if(ch[i][j]>='0'&&ch[i][j]<='9')shuzi+=1;
        if((ch[i][j]>='a'&&ch[i][j]<='z')||(ch[i][j]>='A'&&ch[i][j]<='Z'))zimu+=1;
        if(ispunct(ch[i][j])) qita+=1;}
   cout<<"数字"<<shuzi<<endl;
   cout<<"英文字母"<<zimu<<endl;
   cout<<"其他字符"<<qita<<endl;

    return 0;
}
