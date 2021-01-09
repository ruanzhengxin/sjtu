#include "longlongint.h"



int main()
{   char *a;
    char *b;
    char* c;

    a="112";
    b="242";
    c="0";

    longlongint a1(a);
    longlongint a2(b);
    longlongint a3(c);
    a3=a1+a2;
    cout << a3<< endl;
    return 0;
}
