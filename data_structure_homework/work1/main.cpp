#include <iostream>
#include<string>
#include <stdlib.h>
using namespace std;
class node{
public:
float coff;
int exp;
node *next;
node (){next=NULL;}
node(float n1,int n2,node *p=NULL):coff(n1),exp(n2),next(p){}
};
node *multiply(node *a1,node *a2)
{
    node *res,*p,*tmp,*q,*a22;
    int expp;
    res=new node();
    p=new node();
    tmp=p;
    a1=a1->next;
    a22=a2->next;
    while(a1!=NULL)
    {   a22=a2->next;
        while(a22!=NULL)
        {
            expp=a1->exp+a22->exp;
            p=res->next;
            tmp=res;
            while(p!=NULL&&p->exp<expp)
            {   tmp=p;
                p=p->next;
            }// 找到一个节点 指数相同 或者 指数比结果大  或者 已经找到尾节点 跳出循环
            if(p==NULL||p->exp>expp)
            {
                q=new node(a1->coff*a22->coff,expp,p);
                tmp->next=q;//找到尾节点 或者指数比结果大
            }
            else
            {
                p->coff+=a1->coff*a22->coff;//指数相同
                if(p->coff==0)//相加后 系数为0
                {
                    tmp->next=p->next;
                    delete p;

                }
            }
            a22=a22->next;
        }
        a1=a1->next;
    }
    return res;
}
int main()
{   //输入两个多项式 用链表储存  调用multipy函数 返回结果链表的头节点
    node *res,*p,*p1,*p2,*a2,*a1;
    string pol1,pol2,s1,s2;
    int i=0;
    int n1=0;
    int n2=0;
    int m=0;
    double coff1[1000];
    double coff2[1000];
    int exp1[1000];
    int exp2[1000];
    getline(cin,pol1);
    getline(cin,pol2);
    int len1=int(pol1.length());
    int len2=int(pol2.length());
    pol1+=' ';
    pol2+=' ';
    while(i<len1+1)
    {
        if(pol1[i]!=' '){i++;}
        else{   m=n1;
                while(pol1[m]!=','){m++;}
                s1=pol1.substr(n1,m);
                coff1[n2]=atof(s1.c_str());
                s1="";
                s2=pol1.substr(m+1,i);
                exp1[n2]=atoi(s2.c_str());
                s2="";
                n1=i+1;
                i++;
                n2++;
            }
    }
    p1=new node();
    a1=new node();
    a1=p1;
    for(int k=0;k<n2;k++)
    {
        p1->next=new node(coff1[k],exp1[k],NULL);
        p1=p1->next;
    }
    i=0;
    m=0;
    n1=0;
    n2=0;
    while(i<len2+1)
    {
        if(pol2[i]!=' '){i++;}
        else{   m=n1;
                while(pol2[m]!=','){m++;}
                s1=pol2.substr(n1,m);
                coff2[n2]=atof(s1.c_str());
                s1="";
                s2=pol2.substr(m+1,i);
                exp2[n2]=atoi(s2.c_str());
                s2="";
                n1=i+1;
                i++;
                n2++;
            }
    }
    p2=new node();
    a2=new node();
    a2=p2;
    for(int z=0;z<n2;z++)
    {
        p2->next=new node(coff2[z],exp2[z],NULL);
        p2=p2->next;
    }
     res=new node();
     p=new node();
     res=multiply(a1,a2);
     p=res->next;
     while(p!=NULL)
    {
         cout<<p->coff<<","<<p->exp<<" ";
         p=p->next;
     }

    return 0;
}
