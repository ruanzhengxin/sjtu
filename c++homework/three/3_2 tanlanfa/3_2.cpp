//贪婪法
//平均需要4张纸币

#include <iostream>

using namespace std;

int main()

{  int yiyuan=0,wuyuan=0,shiliuyuan=0,ershisanyuan=0,sanshisanyuan=0,i=1,a=0,s=0,num=0;
   for(i=1;i<=99;++i)
   {   a=i;
       while(a>=33){sanshisanyuan++;a-=33;}
       while(a>=23){ershisanyuan++;a-=23;}
       while(a>=16){shiliuyuan++;a-=16;}
       while(a>=5){wuyuan++;a-=5;}
       while(a>=1){yiyuan++;a-=1;}
       num=yiyuan+wuyuan+shiliuyuan+ershisanyuan+sanshisanyuan;
       a=0;
       s=s+num;
       cout<<i<<"   "<<num<<endl;


       num=0;
       yiyuan=0;
       wuyuan=0;
       shiliuyuan=0;
       ershisanyuan=0;
       sanshisanyuan=0;

   }
    cout << s/99 << endl;
    return 0;
}
