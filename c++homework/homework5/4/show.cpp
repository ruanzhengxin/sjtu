#include "four.h"
void showmessage(studentT studentarray[100],int *len)
{
    int i;
    cout<<"ѧ��"<<"         "<<"����"<<"       "<<"��ѧ�ɼ�"<<"      "<<"Ӣ��ɼ�"<<"        "<<"����ɼ�"<<endl;
    for(i=0;i<*len;i++)
    {
        cout<<studentarray[i].number<<"         "<<studentarray[i].name<<"        "<<studentarray[i].math<<"             "<<studentarray[i].english<<"             "<<studentarray[i].physic<<endl;
    }
}
