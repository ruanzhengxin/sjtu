#include <iostream>
#include<string>
#include <stdlib.h>
using namespace std;
template <class elemType>
class queue
 { public:
        virtual bool isEmpty() = 0;                  //�жӿ�
        virtual void enQueue(const elemType &x) = 0; //����
        virtual elemType  deQueue() = 0;             //����
	virtual elemType getHead() = 0;              //����ͷԪ��
        virtual ~queue() {}
        virtual bool usedsize()=0;                          //����������
 };
template <class elemType>
class linkQueue: public queue<elemType>
 { private:
       struct node {
            elemType  data;
	  node *next;
 	  node(const elemType &x, node *N = NULL)
                  {	data = x; next = N;}
	  node():next(NULL) {}
	  ~node() {}
	};
	node *front, *rear;
public:
     linkQueue();

     ~linkQueue();
     bool isEmpty(){return front == NULL;}
     void enQueue(const elemType &x) ;
     elemType deQueue();
     bool usedsize(){return front->next==NULL;}
     elemType getHead(){return front->data;}
};


template <class elemType>
linkQueue<elemType>::linkQueue()
{
   front = rear = NULL;
}
template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
    if (rear == NULL)
  	    front = rear = new node(x);
    else
	         rear = rear->next = new node(x);
}
template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
    node *tmp = front;
    elemType value = front->data;
    front = front->next;
    if (front == NULL) rear = NULL;
    delete tmp;
    return value;
}


template <class elemType>
linkQueue<elemType>::~linkQueue()
{
	   node *tmp;
	   while (front != NULL) {
		      tmp = front;
		      front = front->next;
		      delete tmp;
	   }
}
void enter_int_stack(linkQueue<int> &q1,linkQueue<int> &q2,int val)
{
       //linkQueue<int> p1 = q1;//��Ҫ��ӵĶ���
		if(q1.isEmpty()){
			q2.enQueue(val);
		}
		else q1.enQueue(val);
}
int pop_int_Stack(linkQueue<int> &q1,linkQueue<int> &q2){
		/*linkQueue<int> p1 ;//ָ��Ҫ���ӵ��Ǹ�����
		linkQueue<int> p2;//��Զָ����Ӻ�Ԫ����Ҫ���õĶ���*/
		int num=0;
		if(q1.isEmpty()&&q2.isEmpty()){//�����Ӷ�Ϊ��
			return -1;
		}
		if(!q1.isEmpty()){
			while(!q1.usedsize()){//�����ӵĶ������γ��Ӳ��뵽��һ���У�ֱ��ʣһԪ��
			q2.enQueue(q1.getHead());
			q1.deQueue();
		}

		num = q1.getHead();
		q1.deQueue();
		}
		else{
			while(!q2.usedsize()){
			q1.enQueue(q2.getHead());
			q2.deQueue();
		}

		num = q2.getHead();
		q2.deQueue();
		}

		return num;
	}
void enter_char_stack(linkQueue<char> &q1,linkQueue<char> &q2,char val)
{
       if(q1.isEmpty()){
			q2.enQueue(val);
		}
		else q1.enQueue(val);
}
char pop_char_Stack(linkQueue<char> &q1,linkQueue<char> &q2){

		char num;
		if(q1.isEmpty()&&q2.isEmpty()){//�����Ӷ�Ϊ��
			return -1;
		}
		if(!q1.isEmpty()){
			while(!q1.usedsize()){//�����ӵĶ������γ��Ӳ��뵽��һ���У�ֱ��ʣһԪ��
			q2.enQueue(q1.getHead());
			q1.deQueue();
		}

		num = q1.getHead();//�õ���Ҫ���ӵ�Ԫ��
		q1.deQueue();//�����Ψһʣ�µ�Ԫ��Ū��ȥ��������
		}
		else{
			while(!q2.usedsize()){//�����ӵĶ������γ��Ӳ��뵽��һ���У�ֱ��ʣһԪ��
			q1.enQueue(q2.getHead());
			q2.deQueue();
		}

		num = q2.getHead();//�õ���Ҫ���ӵ�Ԫ��
		q2.deQueue();//�����Ψһʣ��q1.deQueue();��Ԫ��Ū��ȥ��������
		}

		return num;
	}
int main()
{   //�ַ������� ���� ģ�����ջ  ��ȡ������Ϣ
    string choice;
    string content;
    getline(cin,choice);
    getline(cin,content);
    int a[5]={};

    int n1=0,n2=0;
    string s1;
    linkQueue<int> q1;
    linkQueue<int> q2;
    linkQueue<char> p1;
    linkQueue<char> p2;
    if(choice=="int"){content+=' ';
        for(int i=0;i<content.length();i++)
        {
            if(content[i]==' ')
                {
                 s1=content.substr(n1,i);
                 a[n2]=atoi(s1.c_str());
                 s1="";
                 n2++;
                 n1=i+1; }
        }

       enter_int_stack(q1,q2,a[0]);
       enter_int_stack(q1,q2,a[1]);
       cout<<pop_int_Stack(q1,q2)<<" ";
       enter_int_stack(q1,q2,a[2]);
       cout<<pop_int_Stack(q1,q2)<<" ";
       cout<<pop_int_Stack(q1,q2)<<" ";
       enter_int_stack(q1,q2,a[3]);
       enter_int_stack(q1,q2,a[4]);
       cout<<pop_int_Stack(q1,q2)<<" ";
       cout<<pop_int_Stack(q1,q2)<<" ";
  }
    if(choice=="char"){
        enter_char_stack(p1,p2,content[0]);
       enter_char_stack(p1,p2,content[2]);
       cout<<pop_char_Stack(p1,p2)<<" ";
       enter_char_stack(p1,p2,content[4]);
       cout<<pop_char_Stack(p1,p2)<<" ";
       cout<<pop_char_Stack(p1,p2)<<" ";
       enter_char_stack(p1,p2,content[6]);
       enter_char_stack(p1,p2,content[8]);
       cout<<pop_char_Stack(p1,p2)<<" ";
       cout<<pop_char_Stack(p1,p2)<<" ";
        }
   return 0;
}
