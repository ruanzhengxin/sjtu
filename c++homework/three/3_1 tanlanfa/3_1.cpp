//̰�ķ�
//ƽ����Ҫ4��

#include <iostream>

using namespace std;

int main()
{  int yiyuan=0,wuyuan=0,shiyuan=0,ershiyuan=0,wushiyuan=0,a=0,s=0,num=0,i;
   for(i=1;i<=99;++i)
   {a=i;
   while(a>=50){wushiyuan++;a-=50;}
   while(a>=20){ershiyuan++;a-=20;}
   while(a>=10){shiyuan++;a-=10;}
   while(a>=5){wuyuan++;a-=5;}
   while(a>=1){yiyuan++;a-=1;}
   num=yiyuan+wuyuan+shiyuan+ershiyuan+wushiyuan;
   cout<<i<<"Ԫ��Ҫ"<<num<<"��ֽ��"<<endl;
   s=s+num;
   a=0;
   yiyuan=0;
   wuyuan=0;
   shiyuan=0;
   ershiyuan=0;
   wushiyuan=0;
   }
    cout<< s/99 << endl;
    return 0;
}
