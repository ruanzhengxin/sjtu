#include <iostream>

using namespace std;

int main()
{ double r,s,v;

    cout << "输入球体半径" << endl;
    cin>>r;
    s=3.14*4*r*r;
    v=4*3.14*r*r*r/3;
    cout<<"球体面积="<<s<<"球体体积="<<v<<endl;

    return 0;
}
