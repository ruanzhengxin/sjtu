//指针数组中最短字符串长度。
#include<iostream>
#include<cstring>
using namespace std;
int minlen(char*str[],int n)
{
	for(int i=0;i<n;i++)
	{	
		bool flag=true;
		for(int k=0;k<n;k++)
		if(strlen(str[i])>strlen(str[k]))flag=false;
		if(flag)return strlen(str[i]);
	}
	
}
int main()
{	
	char*str[6];int i=0;char a[80];
	cout<<"请输入字符串个数：";
	int n;
	cin>>n;
	
	
	
	while(i<n)
	{	cin>>a;
		str[i]=new char[strlen(a)+1];
		strcpy(str[i],a);
		i++;
		
	}
	cout<<minlen(str,n) ;
	
	 
} 
