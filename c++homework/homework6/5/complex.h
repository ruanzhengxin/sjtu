#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED
#include<iostream>
#include<cstring>
#include"longlongint.h"
using namespace std;
class Complex{
	friend Complex operator+(Complex x, Complex y);
    friend ostream& operator<<(ostream &os,const Complex &obj);
	private:
	longlongint real;
	longlongint imag;
public:


	Complex(char *a="0",char *b="0"):real(a), imag(b) {}
};



#endif // COMPLEX_H_INCLUDED
