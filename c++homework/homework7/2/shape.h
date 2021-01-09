#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED
#include<iostream>
#include<cmath>
using namespace std;
class shape{
  public:
      virtual double getarea()const=0;
      virtual void display()=0;
};
class triangle:public shape{
  protected:
      double a,b,c;
  public:
    triangle(double aa,double bb,double cc)
    {
        a=aa;
        b=bb;
        c=cc;
    }
    virtual double getarea()const
    {
        double p;
        p=(a+b+c)/2;
        return (sqrt(p*(p-a)*(p-b)*(p-c)));
    }
    virtual void display()
    {
        cout<<"The triangle's area is "<<getarea()<<endl;
    }
};
class rectangle:public shape{
protected:
    double a,b;
public:
    rectangle(double aa,double bb)
    {
        a=aa;
        b=bb;
    }
    virtual double getarea()const
    {
        return (a*b);

    }
    virtual void display()
    {
        cout<<"The rectangle'area is "<<getarea()<<endl;
    }

};
class square:public rectangle{
 public:
     square(double aa):rectangle(aa,aa){}
     virtual double getarea()const
     {
         return (a*b);
     }
     virtual void display()
    {
        cout<<"The square'area is "<<getarea()<<endl;
    }
};
class ellipse:public shape{
 protected:
     double a,b;
 public:
    ellipse(double aa,double bb)
    {
        a=aa;
        b=bb;
    }
    virtual double getarea()const
     {
         return (a*b*3.14);
     }
     virtual void display()
    {
        cout<<"The ellipse'area is "<<getarea()<<endl;
    }
};
class circle:public ellipse{
public:
    circle(double aa):ellipse(aa,aa){}
    virtual double getarea()const
    {
        return (a*b*3.14);
    }
     virtual void display()
    {
        cout<<"The circle'area is "<<getarea()<<endl;
    }
};


#endif // SHAPE_H_INCLUDED
