#ifndef ACCOUNT_H_INCLUDED
#define ACCOUNT_H_INCLUDED
#include<iostream>
using namespace std;
class savingaccount{
 int account;
 struct date;
 double money;

 public:
     void creataccount(int a);
     void salary(double x);
     void display();

     };
struct date{
    int year;
    int month;
    int day;};


#endif // ACCOUNT_H_INCLUDED
