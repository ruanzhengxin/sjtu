#include "four.h"
void addmessage(studentT studentarray[100],int *len)
{
   char *str1,*str2;
   str1=new char[5];
   str2=new char[10];
   cout<<"����ѧ��"<<endl;
   cin>>str1;

   studentarray[*len].number=str1;


   cout<<"��������ɼ�"<<endl;
   cin>>studentarray[*len].math>>studentarray[*len].english>>studentarray[*len].physic;

   cout<<"��������"<<endl;
   cin>>str2;
   studentarray[*len].name=str2;
  *len+=1;


}
void changemessage(studentT studentarray[100],int *len)
{
    cout<<"����Ҫ������Ϣ��ѧ��ѧ��"<<endl;
    char *number;
    number=new char[6];
    cin>>number;
    int i;
    for(i=0;i<*len;i++)
        if(strcmp(studentarray[i].number,number)==0)break;
     char *str1,*str2;
   str1=new char[5];
   str2=new char[10];
   cout<<"����ѧ��"<<endl;
   cin>>str1;

   studentarray[i].number=str1;


   cout<<"��������ɼ�"<<endl;
   cin>>studentarray[i].math>>studentarray[i].english>>studentarray[i].physic;

   cout<<"��������"<<endl;
   cin>>str2;
   studentarray[i].name=str2;
   cout<<"�޸����"<<endl;

}
