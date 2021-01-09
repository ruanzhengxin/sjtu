#include"complex.h"


Complex operator+(Complex x, Complex y)
{ Complex tmp;

   tmp.real = x.real + y.real;
   tmp.imag = x.imag + y.imag;
   return tmp;
}
ostream& operator<<(ostream &os, const Complex &obj)
{

  cout << '(' << obj.real << " + " << obj.imag << "i" << ')';
  return os;
}
