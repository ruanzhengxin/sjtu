#include <iostream>

using namespace std;

struct numberT{
    int shibu;
    int xubu;
    };
numberT product(const numberT n1,const numberT n2)
{
    numberT res;
    res.shibu=n1.shibu*n2.shibu-n1.xubu*n2.xubu;
    res.xubu=n1.xubu*n2.shibu+n1.shibu*n2.xubu;
    return(res);
}
numberT add(const numberT n1,const numberT n2)
{
    numberT res;
    res.shibu=n1.shibu+n2.shibu;
    res.xubu=n1.xubu+n2.xubu;
    return(res);
}
int main()
{  numberT n1,n2,result1,result2;

  cin>>n1.shibu>>n1.xubu>>n2.shibu>>n2.xubu;
  result1=add(n1,n2);
  cout<<"¼Ó·¨"<<result1.shibu<<"+"<<result1.xubu<<"i"<<endl;
  result2=product(n1,n2);
  cout<<"³Ë·¨"<<result2.shibu<<"+"<<result2.xubu<<"i"<<endl;
    return 0;
}
