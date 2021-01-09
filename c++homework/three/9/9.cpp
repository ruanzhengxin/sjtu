#include <iostream>
#include<cstring>

using namespace std;

int main()
{ int i=0,j=0,n=0,e,f;
 char str[80];

 cin.getline(str,80);

 e=strlen(str);
 for(i=0;i<e;i++)
    if(str[i]>='a'&&str[i]<='z')str[i]='\0';

for(j=0;j<e;j++)
 {
     if(str[j]>='0'&&str[j]<='9')

    n=n*10+str[j]-'0';

 }cout<<n<<endl;



    return 0;
}
