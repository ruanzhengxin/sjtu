//贪心法
//平均需要4张

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
   cout<<i<<"元需要"<<num<<"张纸币"<<endl;
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

//穷举法
//平均纸币数为4

#include <iostream>

using namespace std;

int main()
  { int i,yiyuan=0,wushiyuan=0, ershiyuan=0,shiyuan=0,wuyuan=0,num=99,s=0,a=0,x=0;
    double e;
    for(i=1;i<=99;++i)
    {   a=i;
       for(wushiyuan=0;wushiyuan<=2;++wushiyuan)
        for( ershiyuan=0; ershiyuan<=((a-50*wushiyuan)/20);++ ershiyuan)
         for(shiyuan=0;shiyuan<=((a-50*wushiyuan-20* ershiyuan)/10);++shiyuan)
          for(wuyuan=0;wuyuan<=((a-50*wushiyuan-20* ershiyuan-10*shiyuan)/5);++wuyuan)
           for(yiyuan=0;yiyuan<=a-50*wushiyuan-20* ershiyuan-10*shiyuan-5*wuyuan;++yiyuan)
            if(wushiyuan>=0&& ershiyuan>=0&&shiyuan>=0&&wuyuan>=0)num=yiyuan+wuyuan+shiyuan+ ershiyuan+wushiyuan;










      s=s+num;
      a=0;
      num=99;
      x=0;
      yiyuan=0;
      wuyuan=0;
     shiyuan=0;
     ershiyuan=0;
     wushiyuan=0;
    }e=s/99.;
    cout<<e<<endl;
    return 0;
 }

