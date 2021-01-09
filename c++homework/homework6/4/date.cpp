#include"date.h"
void Date::setDate(int a,int b,int c)
{
    month=a;
    day=b;
    year=c;
}
bool operator<(const Date &d1,const Date &d2)
{
    if(d1.year<d2.year)return true;
     else if(d1.year>d2.year)return false;
        else if(d1.month<d2.month)return true;
         else if(d1.month>d2.month)return false;
            else if(d1.day<d2.day)return true;
              else return false;


}
 ostream& operator<<(ostream& os,const Date &obj)
 {  switch(obj.month)
    {case 1:os<<" January"<<"  "<<obj.day<<", "<<obj.year<<endl;break;
     case 2:os<<" February "<<"  "<<obj.day<<", "<<obj.year<<endl;break;
     case 3:os<<" March"<<"  "<<obj.day<<", "<<obj.year<<endl;break;
     case 4:os<<" April"<<"  "<<obj.day<<", "<<obj.year<<endl;break;
     case 5:os<<" May"<<"  "<<obj.day<<", "<<obj.year<<endl;break;
     case 6:os<<" June"<<"  "<<obj.day<<", "<<obj.year<<endl;break;
     case 7:os<<" July"<<"  "<<obj.day<<", "<<obj.year<<endl;break;
     case 8:os<<" August"<<"  "<<obj.day<<", "<<obj.year<<endl;break;
     case 9:os<<" September"<<"  "<<obj.day<<", "<<obj.year<<endl;break;
     case 10:os<<" October"<<"  "<<obj.day<<", "<<obj.year<<endl;break;
     case 11:os<<" November "<<"  "<<obj.day<<", "<<obj.year<<endl;break;
     case 12:os<<" December"<<"  "<<obj.day<<", "<<obj.year<<endl;break;}

     return os;
 }
 Date &Date::operator++()
 {
     ++day;
     re();
     return *this;
 }
 Date &Date::operator+=(int a)
 {
     day+=a;
     re();
     return *this;
 }
 Date Date::operator++(int x)
 {
     Date tmp=*this;
     ++day;
     re();
     return tmp;
 }
  Date::Date(int a,int b,int c)
  {   bool flag=true;
      if(c%400==0||(c%100!=0&&c%4==0))
        {
            if(a==2&&b>29)flag=false;
        }
      else if(b>28&&b==2)flag=false;
      switch(a)
      {case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:if(b>31)flag=false;break;

      case 4:
      case 6:
      case 9:
      case 11:if(b>30)flag=false;break;
      }
      if(b<=0||b>31||a<=0||a>12||c<=0)flag=false;
    if(flag){month=a;day=b;year=c;}
     else {month=1;day=1;year=1900;}
}
 void Date::re()
 {
     if((month==1||month==3||month==5||month==7||month==8||month==10)&&day>31){month+=day/31;day=day%31;}
     if((month==2||month==4||month==6||month==9||month==11)&&day>30){month+=day/30;day=day+day%30;}
     if(month==12&&day>31){month=day/31;day=day%31;++year;}
 }























