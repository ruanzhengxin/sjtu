#include"longlongint.h"
int main()
{   char *a;
    char *b;
    char *c;
    int i,maxs;
    a="11111111111111111111111118";
    b="2222222222222222222222229";

    if(strlen(a)>strlen(b))maxs=strlen(a);
      else maxs=strlen(b);
    longlongint a1(a);
    longlongint a2(b);
    longlongint a3(c);
    a3.add(a1,a2);

    c=a3.getnum();
    cout<<"11111111111111111111111118"<<"+"<<"2222222222222222222222229"<<"=";
    for(i=0;i<maxs;i++)
        cout<<c[i];
    return 0;
}
