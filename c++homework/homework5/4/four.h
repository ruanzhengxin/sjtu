#ifndef FOUR_H_INCLUDED
#define FOUR_H_INCLUDED

#include<cstring>
#include <iostream>


using namespace std;
struct studentT{
  char *number;
  char *name;
  int math;
  int english;
  int physic;};


void addmessage(studentT studentarray[100],int *len);
void changemessage(studentT studentarray[100],int *len);
void showmessage(studentT studentarray[100],int *len);
void search_by_number(studentT studentarray[100],int *len);
void search_by_name(studentT studentarray[100],int *len);
void sort_by_number(studentT studentarray[100],int *len);
void sort_by_score(studentT studentarray[100],int *len);








#endif // FOUR_H_INCLUDED
