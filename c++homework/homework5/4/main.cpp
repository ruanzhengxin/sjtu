#include "four.h"



int main()
{   studentT studentarray[100]={{"00001","����",98,99,99},{"00002","����",60,60,60},{"00003","����",75,99,69},{"00005","����",75,89,71},{"00004","����",78,89,31}};
    int x,len;
    len=5;

    while(x!=0)
    {
    cout<<"��ӭʹ�óɼ�����ϵͳ"<<endl;
    cout<<"1-���ѧ����Ϣ"<<endl;
    cout<<"2-�޸�ѧ����Ϣ"<<endl;
    cout<<"3-��ʾȫ��ѧ����Ϣ"<<endl;
    cout<<"4-��ѧ�Ų�ѯѧ����Ϣ"<<endl;
    cout<<"5-��������ѯѧ����Ϣ"<<endl;
    cout<<"6-��ѧ����������"<<endl;
    cout<<"7-���ֽܷ�������"<<endl;
    cout<<"0-�˳�"<<endl;
    cin>>x;
    switch(x)
    {
        case 1:{addmessage(studentarray,&len);continue;}
        case 2:{changemessage(studentarray,&len);continue;}
        case 3:{showmessage(studentarray,&len);continue;}
        case 4:{search_by_number(studentarray,&len);continue;}
        case 5:{search_by_name(studentarray,&len);continue;}
        case 6:{sort_by_number(studentarray,&len);continue;}
        case 7:{sort_by_score(studentarray,&len);continue;}
        case 0:break;
    }
    }


    return 0;
}
