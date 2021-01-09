#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED
#include<iostream>
#include<cstring>
using namespace std;
class employee{
protected:
    char* name;
    char* number;
public:
    virtual void display()=0;

    virtual int salary()const=0;
    employee(char* a,char* b)
    {   name=new char[strlen(a)+1];
        number=new char[strlen(b)+1];
        strcpy(name,a);
        strcpy(number,b);
    }

};
class salaried_employee:public employee{
 protected:
     int salarys;
 public:
    salaried_employee(char* a,char* b,int c):employee(a,b),salarys(c){}

    virtual int salary()const
    {
        return salarys;
    }
     virtual void display()
    {
        cout<<name<<"   "<<number<<"       "<<salary()<<endl;
    }
};
class hourly_employee:public employee{
 protected:
     int salary_per_hour;
     int hour;

 public:
    hourly_employee(char* a,char* b,int c,int d):employee(a,b)
    {salary_per_hour=c,hour=d;}
    virtual int salary()const
    {
        if(hour<40)return (salary_per_hour*hour);
        else return (40*salary_per_hour+(hour-40)*2*salary_per_hour);
    }
     virtual void display()
    {
        cout<<name<<"   "<<number<<"       "<<salary()<<endl;
    }
};
class commission_employee:public employee{
protected:
    int sale;
    double rate;

public:
    commission_employee(char* a,char* b,int c,double d):employee(a,b)
    {
        sale=c;
        rate=d;
    }
    virtual int salary()const
    {
        return(sale*rate);
    }
     virtual void display()
    {
        cout<<name<<"   "<<number<<"       "<<salary()<<endl;
    }
    };
class base_salary_plus_commission_employee:public commission_employee{
protected:
    int base_salary;
public:
    base_salary_plus_commission_employee(char* a,char* b,int c,double d,int e): commission_employee(a,b,c,d)
    {
        base_salary=e;
    }
    virtual int salary()const
    {
        return (sale*rate+base_salary);
    }
     virtual void display()
    {
        cout<<name<<"   "<<number<<"       "<<salary()<<endl;
    }
    };

#endif // EMPLOYEE_H_INCLUDED
