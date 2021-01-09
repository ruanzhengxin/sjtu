#include "four.h"



int main()
{   studentT studentarray[100]={{"00001","张三",98,99,99},{"00002","李四",60,60,60},{"00003","王五",75,99,69},{"00005","赵六",75,89,71},{"00004","陈七",78,89,31}};
    int x,len;
    len=5;

    while(x!=0)
    {
    cout<<"欢迎使用成绩管理系统"<<endl;
    cout<<"1-添加学生信息"<<endl;
    cout<<"2-修改学生信息"<<endl;
    cout<<"3-显示全部学生信息"<<endl;
    cout<<"4-按学号查询学生信息"<<endl;
    cout<<"5-按姓名查询学生信息"<<endl;
    cout<<"6-按学号升序排序"<<endl;
    cout<<"7-按总分降序排序"<<endl;
    cout<<"0-退出"<<endl;
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
