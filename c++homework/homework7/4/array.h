#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED
#include<iostream>
using namespace std;
template <class T>
class Array
{  int low;
   int high;
   T *storage;
public:
  Array(int lh = 0, int rh = 0): low(lh), high(rh)
               {storage = new T [high - low + 1]; }
  Array(const Array &arr);

  Array &operator=(const Array & a);

  T & operator[](int index);

  ~Array() {delete [] storage; }
};
template <class T>
Array<T> &Array<T>::operator=(const Array<T> & a)
{ if (this == &a) return *this;   //防止自己复制自己
  delete [] storage; // 归还空间
  low = a.low;
  high = a.high;
  storage = new T [high - low + 1];
  for (int i=0; i <= high - low; ++i) storage[i] = a.storage[i];
  return *this;
}
template <class T>
Array<T>::Array(const Array<T> &arr)
{   low = arr.low;
     high = arr.high;
     storage = new T [high - low + 1];
     for (int i = 0; i < high -low + 1; ++i)  storage[i] = arr.storage[i];
}

template <class T>
T & Array<T>::operator[](int index)
{ if (index < low || index > high) {cout << "下标越界"; exit(-1); }
   return storage[index - low];
}
template<class T>
class newarray:public Array<T>{
public:
    newarray(int rh=0):Array(0,rh){};

};


#endif // ARRAY_H_INCLUDED
