#include "four.h"


void search_by_number(studentT studentarray[100],int *len)
{
    cout<<"����Ҫ������ѧ��"<<endl;
    char *number;
    number=new char[6];
    cin>>number;
    int i;
    for(i=0;i<*len;i++)
        if(strcmp(studentarray[i].number,number)==0)
    { cout<<"ѧ��"<<"         "<<"����"<<"       "<<"��ѧ�ɼ�"<<"      "<<"Ӣ��ɼ�"<<"        "<<"����ɼ�"<<endl;
      cout<<studentarray[i].number<<"         "<<studentarray[i].name<<"        "<<studentarray[i].math<<"             "<<studentarray[i].english<<"             "<<studentarray[i].physic<<endl;
    }
}
void search_by_name(studentT studentarray[100],int *len)
{
    cout<<"����Ҫ����������"<<endl;
    char *name;
    name=new char[10];
    cin>>name;
    int i;
    for(i=0;i<*len;i++)
        if(strcmp(studentarray[i].name,name)==0)
    {cout<<"ѧ��"<<"         "<<"����"<<"       "<<"��ѧ�ɼ�"<<"      "<<"Ӣ��ɼ�"<<"        "<<"����ɼ�"<<endl;
      cout<<studentarray[i].number<<"         "<<studentarray[i].name<<"        "<<studentarray[i].math<<"             "<<studentarray[i].english<<"             "<<studentarray[i].physic<<endl;
    }
}
