//穷举法
//平均纸币数为4.15

#include <iostream>

using namespace std;

int main()
  { int i,yiyuan=0,sanshisanyuan=0,ershisanyuan=0,shiliuyuan=0,wuyuan=0,num=99,s=0,a=0,x=0;
    double e;
    for(i=1;i<=99;++i)
    {   a=i;
       for(sanshisanyuan=0;sanshisanyuan<=3;++sanshisanyuan)
        for(ershisanyuan=0;ershisanyuan<=((a-33*sanshisanyuan)/23);++ershisanyuan)
         for(shiliuyuan=0;shiliuyuan<=((a-33*sanshisanyuan-23*ershisanyuan)/16);++shiliuyuan)
          for(wuyuan=0;wuyuan<=((a-33*sanshisanyuan-23*ershisanyuan-16*shiliuyuan)/5);++wuyuan)
           for(yiyuan=0;yiyuan<=a-33*sanshisanyuan-23*ershisanyuan-16*shiliuyuan-5*wuyuan;++yiyuan)
            if(sanshisanyuan>=0&&ershisanyuan>=0&&shiliuyuan>=0&&wuyuan>=0)num=yiyuan+wuyuan+shiliuyuan+ershisanyuan+sanshisanyuan;










      s=s+num;
      a=0;
      num=99;
      x=0;
      yiyuan=0;
      wuyuan=0;
     shiliuyuan=0;
     ershisanyuan=0;
     sanshisanyuan=0;
    }e=s/99.;
    cout<<e<<endl;
    return 0;
 }



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

