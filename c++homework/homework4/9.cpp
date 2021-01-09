//julian-->公历月日
#include<iostream>
using namespace std;
int main()
{
	int month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	char*str[13]={"NULL","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	int year,day,yue,ri;
	cin>>year>>day;
	if(year%4==0&&year%100!=0||year%400==0)
		month[2]=29;
	if(day<31)cout<<"Jan"<<day;
	else 
	{
		for(int i=1;i<=12;i++)
		{
			day=day-month[i];
			if(day<=month[i+1])
			{
			yue=i+1;ri=day;break;}
			
		}
	}
	cout<<str[yue]<<' '<<ri;
	 }
