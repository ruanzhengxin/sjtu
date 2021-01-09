#ifndef LONGLONGINT_H_INCLUDED
#define LONGLONGINT_H_INCLUDED
#include<iostream>
#include<cstring>
using namespace std;
class longlongint{
   char *num;
   public:
       longlongint(char *a);
       longlongint(const longlongint &ob);
       void add(const longlongint a,const longlongint b);
       char* getnum();
};


#endif // LONGLONGINT_H_INCLUDED
