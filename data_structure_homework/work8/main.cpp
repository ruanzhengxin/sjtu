#include <iostream>
#include<string>
#include <stdlib.h>
using namespace std;
template <class KEY, class OTHER>
struct SET {
    KEY key;
    OTHER other;
    int time;
};

template <class KEY, class OTHER>
class dynamicSearchTable {
public:

    virtual void insert(SET<KEY, OTHER> &x) = 0;
    virtual ~dynamicSearchTable() {};
};

template <class KEY, class OTHER>
class closeHashTable:public dynamicSearchTable<KEY, OTHER> {
  private:
      struct node { //散列表的结点类
          SET <KEY, OTHER>  data;
		    int state;  //0 -- empty   1 -- active   2 -- deleted
		    node() {state = 0;}
	  };
      node *array;
      int  size;
      int paramater;
      int (*key)(const KEY &x);
      static int defaultKey(const int &x) {return x;}
  public:
     closeHashTable(int length = 101, int paramater=101,int (*f)(const KEY &x) = defaultKey) ;
     ~closeHashTable() {delete [] array;}
     void insert(SET<KEY, OTHER> &x);
     void print();
};
template <class KEY, class OTHER>
closeHashTable<KEY, OTHER>::closeHashTable
            (int length,int p, int (*f)(const KEY  &x) )
{   paramater=p;
	size = length;
	array = new node[size];
	key = f;
}
template <class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::insert(SET<KEY, OTHER> &x)
{
	   int initPos, pos ;
       x.time=0;
	   initPos = pos = key(x.key) % paramater;
	   do {
              if (array[pos].state != 1) {       // 找到空单元
                   array[pos].data = x;
                   array[pos].state = 1;
                   return;
              }
         // if(pos>paramater||pos==paramater-1||pos==paramater){pos++;}
         //else pos = (pos+1) % paramater;
	        pos++;
	        if(pos==size){pos=0;}
	        x.time++;
        } while (pos != initPos);
}

template <class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::print()
{
    for(int i=0;i<size;i++)
        { if(array[i].state==1){cout<<array[i].data.key<<" ";}
         else cout<<-1<<" ";}
    cout<<endl;
    for(int k=0;k<size;k++)
    {
        if(array[k].state==1){cout<<array[k].data.time+1<<" ";}
        else cout<<0<<" ";
    }

}
int main()
{   string s1,s2,s;
    getline(cin,s1);
    getline(cin,s2);
    int p,m,n,j=0,k=0;
    int a[2];
    while(k<s1.length())
       {  if(s1[k]!=' '){k++;}
          else{a[j]=k;j++;k++;}
        }
    s=s1.substr(0,a[0]);
    p=atoi(s.c_str());
    s=s1.substr(a[0],a[1]);
    m=atoi(s.c_str());
    s=s1.substr(a[1],s1.length());
    n=atoi(s.c_str());
    SET<int, char *> b[n];
    int c[n+1];

    k=0;
    j=1;
    while(k<s2.length())
       {  if(s2[k]!=' '){k++;}
          else{c[j]=k;j++;k++;}
        }
    c[0]=0;
    c[n]=s2.length();
    for(int z=0;z<n;z++)
    {
        b[z].key=atoi(s2.substr(c[z],c[z+1]).c_str());
    }
    closeHashTable<int, char *> hashtable(m,p);
    for(int i=0;i<n;i++) hashtable.insert(b[i]);
    for(int o=0;o<m;o++){cout<<o<<" ";}
    cout<<endl;
    hashtable.print();


    return 0;
}
