#include <iostream>

using namespace std;

int main()
{  int i,p=1,s=0;
   for(i=1;i<=10;++i)
   {   p=p*i;
       s=s+p;
}
    cout <<s<< endl;
    return 0;
}
