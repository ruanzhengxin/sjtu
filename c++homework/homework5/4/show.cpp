#include "four.h"
void showmessage(studentT studentarray[100],int *len)
{
    int i;
    cout<<"学号"<<"         "<<"姓名"<<"       "<<"数学成绩"<<"      "<<"英语成绩"<<"        "<<"物理成绩"<<endl;
    for(i=0;i<*len;i++)
    {
        cout<<studentarray[i].number<<"         "<<studentarray[i].name<<"        "<<studentarray[i].math<<"             "<<studentarray[i].english<<"             "<<studentarray[i].physic<<endl;
    }
}
