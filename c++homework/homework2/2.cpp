#include <iostream>
#include<ctime>
#include<cstdlib>


using namespace std;

int main()
{ int num,x,i;
  srand(time(NULL));
  num=rand()*100/(RAND_MAX)+1;
  for(i=0;i<=7;++i){
        cin>>x;
      if(x>num) cout<<"too big"<<endl;
    else if (x==num){cout<<"right"<<endl;
    return 0;}

         else cout<<"to small"<<endl;

   }

    return 0;
}
