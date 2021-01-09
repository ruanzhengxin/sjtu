#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED
#include<iostream>
using namespace std;
class Complex{
friend Complex operator+(const Complex &c1,const Complex &c2)
{
    return Complex(c1.real+c2.real,c1.imag+c2.imag);
}
friend Complex operator*(const Complex &c1,const Complex &c2)
{
    return Complex(c1.real*c2.real-c1.imag*c2.imag,c1.real*c2.imag+c2.real*c1.imag);
}
friend bool operator==(const Complex &c1,const Complex &c2)
{
    return c1.real==c2.real&&c1.imag==c2.imag;
}
friend bool operator!=(const Complex &c1,const Complex &c2)
{
    return c1.real!=c2.real||c1.imag!=c2.imag;
}
private:
    double real;
    double imag;
public:
     Complex(double r=0,double i=0)
     {
         real=r;imag=i;
     }
     void display()const{
     if(imag>0)cout<<real<<"+"<<imag<<"i"<<endl;
     else cout<<real<<imag<<"i"<<endl;}

};


#endif // COMPLEX_H_INCLUDED
