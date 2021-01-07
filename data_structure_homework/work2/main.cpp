#include <iostream>
#include <string>
using namespace std;

template<class elemType>
class stack
{
public:
    virtual bool isEmpty()const=0;
    virtual void push (const elemType &x)=0;
    virtual elemType pop()=0;
    virtual elemType top()const=0;
    virtual ~stack(){}
};

template<class elemType>
class seqStack:public stack<elemType>
{
private:
    elemType *data;
    int top_p;
    int maxSize;
    void doubleSpace(){
    elemType *tmp=data;

    data=new elemType[2*maxSize];
    for(int i=0;i<maxSize;++i)data[i]=tmp[i];
    maxSize*=2;
    delete []tmp;
}
public:
    seqStack(int initSize=10){
    data =new elemType[initSize];
    maxSize=initSize;
    top_p=-1;}

    ~seqStack(){delete[] data;}

    bool isEmpty() const{return top_p==-1;}

    void push(const elemType &x){
    if(top_p==maxSize-1)doubleSpace();
    data[++top_p]=x;}

    elemType pop(){return data[top_p--];}
    elemType top()const{return data[top_p];}
};
bool isoperator(char ch)
{
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch==')')
        return true;
    else return false;
}
string infix_to_suffix(const string &infix)
{
    seqStack<char>opstack;
    string result="";
    char topOp;

    for(int i=0;i<infix.size();++i)
        {if(infix[i]==' ')continue;

        switch(infix[i]){
    case ')':
        while(!opstack.isEmpty()&&(topOp=opstack.pop())!='(')
                {
                 result+=topOp;}
                 if(topOp!='('){cout<<"È±×óÀ¨ºÅ"<<endl;
                 return "error";}
        break;
    case'(':opstack.push('(');break;
    case'*':case'/':
        while(!opstack.isEmpty()&&(opstack.top()=='*'||opstack.top()=='/')){result+=opstack.pop();}
        opstack.push(infix[i]);
        break;
    case'+':case'-':
        while(!opstack.isEmpty()&&opstack.top()!='('){result+=opstack.pop();}
        opstack.push(infix[i]);
        break;
    default:

        while(i<infix.size()&&!isoperator(infix[i])&&infix[i]!=' '){result+=infix[i];++i;}

        --i;
        }
}
while(!opstack.isEmpty()){if(opstack.top()=='(')return"error";

result+=opstack.pop();}
return result;}

int main()
{    string input,output;
     getline(cin,input);
     output=infix_to_suffix(input);
     for(int i=0;i<output.size();i++)

     {
         cout<<output[i];
     }
return 0;
}
