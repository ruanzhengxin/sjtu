#include <iostream>

using namespace std;
struct timeT{
 int hour;
 int minute;
 int second;
};
timeT settime(int a,int b,int c)
{
    timeT ti;
    ti.hour=a;
    ti.minute=b;
    ti.second=c;
    return(ti);
}
void increase(timeT *tim)
{
    if(tim->minute==59&&tim->second==59&&tim->hour==23){tim->minute=0;tim->second=0;tim->hour=0;}
     else if(tim->minute==59&&tim->second==59){tim->minute=0;tim->second=0;tim->hour+=1;}
           else     if(tim->second==59){tim->second=0;tim->minute+=1;}
                 else tim->second+=1;



}
void showtime(timeT *tim)
{
    cout<<tim->hour<<":"<<tim->minute<<":"<<tim->second<<endl;
}
int main()
{   int a,b,c;
    timeT time;
    cin>>a>>b>>c;
    time=settime(a,b,c);
    increase(&time);
    showtime(&time);

    return 0;
}
