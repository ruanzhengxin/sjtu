#include "four.h"


void search_by_number(studentT studentarray[100],int *len)
{
    cout<<"输入要搜索的学号"<<endl;
    char *number;
    number=new char[6];
    cin>>number;
    int i;
    for(i=0;i<*len;i++)
        if(strcmp(studentarray[i].number,number)==0)
    { cout<<"学号"<<"         "<<"姓名"<<"       "<<"数学成绩"<<"      "<<"英语成绩"<<"        "<<"物理成绩"<<endl;
      cout<<studentarray[i].number<<"         "<<studentarray[i].name<<"        "<<studentarray[i].math<<"             "<<studentarray[i].english<<"             "<<studentarray[i].physic<<endl;
    }
}
void search_by_name(studentT studentarray[100],int *len)
{
    cout<<"输入要搜索的姓名"<<endl;
    char *name;
    name=new char[10];
    cin>>name;
    int i;
    for(i=0;i<*len;i++)
        if(strcmp(studentarray[i].name,name)==0)
    {cout<<"学号"<<"         "<<"姓名"<<"       "<<"数学成绩"<<"      "<<"英语成绩"<<"        "<<"物理成绩"<<endl;
      cout<<studentarray[i].number<<"         "<<studentarray[i].name<<"        "<<studentarray[i].math<<"             "<<studentarray[i].english<<"             "<<studentarray[i].physic<<endl;
    }
}
