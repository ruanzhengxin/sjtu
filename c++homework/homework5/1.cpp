#include <iostream>
#include<ctime>
#include<cstdlib>
#include<cstring>
using namespace std;

int main()
{  char *articlr[5]={"the","a","one","some","any"};
   char *noun[5]={"boy","girl","dog","town","car"};
   char *verb[5]={"drove","jumped","ran","walked","skipped"};
   char *preposition[5]={"to","from","over","under","on"};
   char *sentence;
   int a,b,c,d,e,f,length,i;
   srand(time(NULL));

   for(i=0;i<20;i++)
   {
    length=0;
   sentence=new char[100];

   a=rand()*5/(RAND_MAX+1);
   strcpy(sentence,articlr[a]);
   length=strlen(articlr[a]);
   sentence[0]=sentence[0]-'a'+'A';
   sentence[length]=' ';
   b=rand()*5/(RAND_MAX+1);
   strcpy(sentence+length+1,noun[b]);
   length=length+strlen(noun[b])+1;
   sentence[length]=' ';
   c=rand()*5/(RAND_MAX+1);
   strcpy(sentence+length+1,verb[c]);
   length=length+strlen(verb[c])+1;
   sentence[length]=' ';
   d=rand()*5/(RAND_MAX+1);
   strcpy(sentence+length+1,preposition[d]);
   length=length+strlen(preposition[d])+1;
   sentence[length]=' ';
   e=rand()*5/(RAND_MAX+1);
   strcpy(sentence+length+1,articlr[e]);
   length=length+strlen(articlr[e])+1;
   sentence[length]=' ';
   f=rand()*5/(RAND_MAX+1);
   strcpy(sentence+length+1,noun[f]);
   length=length+strlen(noun[f])+1;
   sentence[length]='.';
   cout<<sentence<<endl;}


    return 0;
}
