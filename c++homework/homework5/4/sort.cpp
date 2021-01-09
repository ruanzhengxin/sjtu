#include "four.h"



void sort_by_number(studentT studentarray[100],int *len)
{ int i,j,number[100];
 studentT temp;
 for(i=0;i<*len;i++)
    number[i]=studentarray[i].number[4]-'0'+(studentarray[i].number[3]-'0')*10+(studentarray[2].number[3]-'0')*100+(studentarray[1].number[2]-'0')*1000+(studentarray[i].number[0]-'0')*10000;
  for(i=0;i<*len;i++)
   for(j=i;j<*len;j++)
   if(number[i]>number[j]){temp=studentarray[i];
       studentarray[i]=studentarray[j];
       studentarray[j]=temp;}
  cout<<"学号"<<"         "<<"姓名"<<"       "<<"数学成绩"<<"      "<<"英语成绩"<<"        "<<"物理成绩"<<endl;
    for(i=0;i<*len;i++)
    {
        cout<<studentarray[i].number<<"         "<<studentarray[i].name<<"        "<<studentarray[i].math<<"             "<<studentarray[i].english<<"             "<<studentarray[i].physic<<endl;
    }
}
void sort_by_score(studentT studentarray[100],int *len)
{    int i,j,sum[100];
     for(i=0;i<*len;i++)
        sum[i]=studentarray[i].english+studentarray[i].math+studentarray[i].physic;
     studentT temp;
     for(i=0;i<*len;i++)
        for(j=i;j<*len;j++)
     if(sum[i]<sum[j]){temp=studentarray[i];
       studentarray[i]=studentarray[j];
       studentarray[j]=temp;}

    cout<<"学号"<<"         "<<"姓名"<<"       "<<"数学成绩"<<"      "<<"英语成绩"<<"        "<<"物理成绩"<<endl;
    for(i=0;i<*len;i++)
    {
        cout<<studentarray[i].number<<"         "<<studentarray[i].name<<"        "<<studentarray[i].math<<"             "<<studentarray[i].english<<"             "<<studentarray[i].physic<<endl;
    }


}
