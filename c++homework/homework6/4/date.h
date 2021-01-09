#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#include<iostream>
using namespace std;
class Date{
    friend bool operator<(const Date &d1,const Date &d2);

    friend ostream& operator<<(ostream& os,const Date &obj);
private:
    int day;
    int month;
    int year;
    void re();
public:
    Date(int a=1,int b=1,int c=1900);
    void setDate(int a,int b,int c);
    Date &operator++();
    Date &operator+=(int a);
    Date operator++(int x);

    };


#endif // DATE_H_INCLUDED
