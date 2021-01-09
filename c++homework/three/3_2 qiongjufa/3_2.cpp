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
