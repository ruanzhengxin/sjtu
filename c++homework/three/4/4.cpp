#include <iostream>
#include<cstdlib>
#include<ctime>


using namespace std;

int main()
{   int i,j,a=0,c=0,b=0,d=0,e=0,f=0,g=0,h=0,l=0,m=0,n=0,x=0,z=0;

   srand(time(NULL));
    for(i=1;i<=100;i++)
       { z=0;
        for(j=1;j<=10;++j)
        {x=rand()*2/(RAND_MAX+1);
        if(x==0)z+=5;
            else z+=10;}
        switch(z){
        case 50:a+=1;break;
        case 55:b+=1;break;
        case 60:c+=1;break;
        case 65:d+=1;break;
        case 70:e+=1;break;
        case 75:f+=1;break;
        case 80:g+=1;break;
        case 85:h+=1;break;
        case 90:l+=1;break;
        case 95:m+=1;break;
        case 100:n+=1;break;}





        }cout<<a<<"    "<<b<<"    "<<"    "<<c<<"    "<<d<<"     "<<e<<"     "<<f<<"     "<<g<<"    "<<h<<"     "<<l<<"   "<<m<<"     "<<n<<endl;



    return 0;
}
