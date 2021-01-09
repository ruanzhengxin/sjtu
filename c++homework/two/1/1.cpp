#include <iostream>

using namespace std;

int main()
{   int month,year,day,daynum,x;
   bool result;

   do{   cout<<"请输入月 日 年"<<endl;

        cin>>month>>day>>year;
        switch(month){
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:{if (day<=31)
               result=1;
            else result=0;};
                break;
    case 2:{if(((year%4==0&&year%100!=0)||year%400==0)&&day<=29)
            result=1;
            else
               result=0;
                 };break;

    case 4:
    case 6:
    case 9:
    case 11:{if(day<=30)
         result=1;
    else
        result=0;}break; }
   }



     while(result!=1);





  if((year%4==0&&year%100!=0)||year%400==0);
         {
            if(month<=2) daynum=31*(month-1)+day;
          else daynum=31*(month-1)+day+1-(4*month+23)/10;
        };
   if((year%4!=0&&year%100!=0)||year%400!=0);
   {
            if(month<=2) daynum=31*(month-1)+day;
          else daynum=31*(month-1)+day-(4*month+23)/10;
          };
cout<<daynum;




    return 0;
}
