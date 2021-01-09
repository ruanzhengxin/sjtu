#include"longlongint.h"
longlongint &operator+(const longlongint &ob1,const longlongint &ob2)
{
    int maxsize,i;

    if(strlen(ob1.num)>strlen(ob2.num))
        {maxsize=strlen(ob1.num)-1;
          int c;
          c=strlen(ob2.num);
         for(i=0;i<=c;i++)
          ob2.num[maxsize-i]=ob2.num[c-i-1];
         for(i=0;i<strlen(ob1.num)-c;i++)
            ob2.num[i]='0';
          }
         else if(strlen(ob1.num)<strlen(ob2.num))
            {maxsize=strlen(ob2.num)-1;
              int d;
              d=strlen(ob1.num);
            for(i=0;i<=d;i++)
           ob1.num[maxsize-i]=ob1.num[d-i-1];
           for(i=0;i<strlen(ob2.num)-d;i++)
            ob1.num[i]='0';}
            else maxsize=strlen(ob2.num);
               char *a;
                a=new char[maxsize+1];
    int j=0;
    for(i=maxsize;i>=0;i--)
    {
       a[i]=ob1.num[i]-'0'+ob2.num[i]-'0'+j;
        if(a[i]>=10)j=a[i]/10;else j=0;
      a[i]=a[i]%10+'0';    }
      a[maxsize+1]='\0';
   longlongint tmp(a);
   return tmp;

}
longlongint::longlongint(char *a)
{   num=new char[strlen(a)-1];
    strcpy(num,a);
}
ostream& operator<<(ostream &os,const longlongint &obj)
{
    os<<obj.num<<endl;
    return os;
}
longlongint &longlongint::operator=(const longlongint &right)
{
    if(this==&right)return *this;
    strcpy(num,right.num);
    return *this;
}


















