#include <iostream>
#include<string>
#include <stdlib.h>
using namespace std;
template <class  Type>
class queue
 { public:
        virtual bool isEmpty() = 0;                  //�жӿ�
        virtual void enQueue(const  Type &x) = 0; //����
        virtual  Type  deQueue() = 0;             //����
	    virtual  Type getHead() = 0;              //����ͷԪ��
        virtual ~queue() {}
                                 //����������
 };
template <class Type>
class priorityQueue:public queue<Type>
{private:
      int currentSize;
      Type *array;
      int maxSize;

      void doubleSpace();
      void buildHeap( );
      void percolateDown( int hole );
public:
    priorityQueue( int capacity = 100 )
	  { array = new Type[capacity];
         maxSize = capacity;
         currentSize = 0;}
    priorityQueue( const Type data[], int size );
	~priorityQueue() { delete [] array; }
    bool isEmpty()  { return currentSize == 0; }
    void enQueue( const Type & x );
    Type deQueue();
    Type getHead() { return array[1]; }
};
template <class Type>
void priorityQueue<Type>::enQueue( const Type & x )
{  if( currentSize == maxSize - 1 )  doubleSpace();

  // ���Ϲ���
  int hole = ++currentSize;
  for( ; hole > 1 && x < array[ hole / 2 ]; hole /= 2 )
            array[ hole ] = array[ hole / 2 ];
  array[ hole ] = x;
}
template <class Type>
void priorityQueue<Type>::percolateDown( int hole )
{  int child;
   Type tmp = array[ hole ];

   for( ; hole * 2 <= currentSize; hole = child )
      {  child = hole * 2;
         if( child != currentSize && array[ child + 1 ] < array[ child ] )
                child++;
         if( array[ child ] < tmp )   array[ hole ] = array[ child ];
                else    break;
       }
   array[ hole ] = tmp;
 }
template <class Type>
Type priorityQueue<Type>::deQueue()
{ Type minItem;
  minItem = array[ 1 ];
  array[ 1 ] = array[ currentSize-- ];
  percolateDown( 1 );
  return minItem;
 }
template <class Type>
void priorityQueue<Type>::buildHeap( )
{  for ( int i = currentSize / 2; i > 0; i-- )
        percolateDown( i );
}
template <class Type>
priorityQueue<Type>::priorityQueue( const Type *items, int size )
      : maxSize(size + 10 ),  currentSize(size)
{  array = new Type[maxSize];
    for( int i = 0; i < size; i++ )
              array[ i + 1 ] = items[ i ];
   buildHeap();
}
template <class Type>
void priorityQueue<Type>::doubleSpace()
{
      Type *tmp = array;
      maxSize *= 2;
      array = new Type[maxSize];
      for (int i = 0; i < currentSize; ++i)
            array[i] = tmp[i];
      delete [] tmp;
}

struct event
{
    int arrivaltime;
    int servicetime;
    int priority;
    bool operator<(const event &e)const{return priority<e.priority;}
};
// �����ȼ���������  ������ʱ��tʱ �Ƚ�t �� arrivaltime ����������ȼ� ��arrivaltime��=t �Ľ��� Ȼ��ý���servicetime-1
void cpu(priorityQueue<event> &eventqueue)
{  event currentevent;
   priorityQueue<event> tmpqueue;
   int t=0;
   int old=0;
   while(!eventqueue.isEmpty())
   {  while(t<eventqueue.getHead().arrivaltime)
       {
           tmpqueue.enQueue(eventqueue.deQueue());
       }
       currentevent=eventqueue.deQueue();
       currentevent.servicetime-=1;
       t++;
       if(currentevent.priority!=old){cout<<currentevent.priority<<" ";old=currentevent.priority;}
       if(currentevent.servicetime!=0){eventqueue.enQueue(currentevent);}
       while(!tmpqueue.isEmpty())
       {
           eventqueue.enQueue(tmpqueue.deQueue());
       }
   }

}


int main()
{  int x;
   cin>>x;
    priorityQueue<event> eventqueue;
    event Event[x];
    string s;
    string s1,s2,s3;
    cin.ignore();
    int k=0,n[2],a=0;
    for(int i=0;i<x;i++)
    {  getline(cin,s);
       while(k<s.length())
       {  if(s[k]!=' '){k++;}
          else{n[a]=k;a++;k++;}
        }
        s1=s.substr(0,n[0]);
        Event[i].priority=atoi(s1.c_str());
        s2=s.substr(n[0],n[1]);
        Event[i].arrivaltime=atoi(s2.c_str());
        s3=s.substr(n[1],s.length());
        Event[i].servicetime=atoi(s3.c_str());
        a=0;
        k=0;
    }
    for(int m=0;m<x;m++)
    {
        eventqueue.enQueue(Event[m]);
    }

    cpu(eventqueue);
    return 0;

}
