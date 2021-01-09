#ifndef LONGLONGINT_H_INCLUDED
#define LONGLONGINT_H_INCLUDED
#include<iostream>
#include<cstring>
using namespace std;
class longlongint{
    friend longlongint &operator+(const longlongint& ob1,const longlongint& ob2);
    friend ostream& operator<<(ostream &os,const longlongint &obj);
    private:
      char *num;
    public:
       longlongint(char *a);
       longlongint &operator=(const longlongint &right);
};



#endif // LONGLONGINT_H_INCLUDED
