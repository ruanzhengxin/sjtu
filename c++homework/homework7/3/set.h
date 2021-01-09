//集合中不出现数字1000000

#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED
#include<iostream>
using namespace std;
template <class T> class sets;
template<class T>ostream &operator<<(ostream &os,const sets<T>&obj);

template <class T>
class sets{
    friend ostream &operator<<<>(ostream &os,const sets<T>&obj);

private:
    T* setarray;
    int setsize;//数组元素个数
    void reduct()
    {
        int i,j;
        for(i=0;i<setsize;i++)
            for(j=i;j<setsize;j++)
            if(setarray[i]==setarray[j]){setarray[j]=10000000;}
    }
public:
    int getsize()
    {
        return setsize;
    }
    sets(T a=0,T b=0,T c=0,T d=0,T e=0,int f)
    {
        setarray=new T[f];
        setarray[0]=a;
        setarray[1]=b;
        setarray[2]=c;
        setarray[3]=d;
        setarray[4]=e;
        setsize=f;
    }
    ostream &sets<T>::operator<<(ostream &os,const sets<T>&obj)
    {
        os<<endl;
        for(int i=0;i<setsize;i++)
        {   if(obj.setarray[i]!=1000000)
            os<<obj.setarray[i]<<'\t';
            else continue;
        }
        return os;
    }
    sets &operator*(const sets<T>&a,const sets<T>&b)
    { int sizea=a.getsize();
      int sizeb=b.getsize();
       sets<T> tmp(0,0,0,0,0,sizea+sizeb);
       for(int i=0;i<sizea;i++)
        tmp.setarray[i]=a.setarray[i];
       for(i=sizea;i<sizeb+sizea;i++)
        tmp.setarray[i]=b.setarray[i-sizea];
        tmp.reduct();
       return tmp;

    }
    sets &operator+(const sets<T>&a,const sets<T>&b)
    { int sizea=a.getsize();
      int sizeb=b.getsize();
      int k=0
      bool flag;
       sets<T> tmp(0,0,0,0,0,sizea+sizeb);
       for(int i=0;i<sizea;i++)
        {for(int j=0;j<sizeb;j++)
            if(setarray[i]==setarray[j])flag=true;else flag=false;
            if(flag){tmp.setarray[k]=a.setarray[i];k++;break;}


            }
            tmp.reduct();

       return tmp;

    }






   };


#endif // SET_H_INCLUDED
