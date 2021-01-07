#include<iostream>
#include<string>
using namespace std;
template <class elemType>
class stack
 { public:
	  virtual bool isEmpty() const = 0;
	  virtual void push(const elemType &x) = 0;
	  virtual elemType  pop() = 0;
      virtual elemType  top() const = 0;
	  virtual ~stack() {}
	  virtual int stacksize()=0;
 };
template <class elemType>
class linkStack: public stack<elemType>
 { private:
         struct node {
                  elemType  data;
	          node *next;
 	          node(const elemType &x, node *N = NULL)
			      {data = x; next = N;}
	          node():next(NULL) {}
	          ~node() {}
	        };
          node *top_p;
public:
      linkStack();

      ~linkStack();
      bool isEmpty() const;
      void push(const elemType &x);
      elemType  pop();
      elemType top() const;
      int stacksize();
};
template <class elemType>
linkStack<elemType>::linkStack()
{
     top_p = NULL;
}
template <class elemType>
linkStack<elemType>::~linkStack()
{
	  node *tmp;
	  while (top_p != NULL) {
		tmp = top_p;
		top_p = top_p ->next;
		delete tmp;
	}
}
template <class elemType>
void linkStack<elemType>::push(const elemType &x)
{
         top_p = new node(x, top_p);
}

template <class elemType>
int linkStack<elemType>::stacksize()
{  int i=0;
   node *tmp;
   tmp=top_p;
   while(tmp!=NULL){i++;tmp=tmp->next;}

   return i;

}
template <class elemType>
elemType linkStack<elemType>::pop()
{
    node *tmp = top_p;
    elemType x = tmp->data;

    top_p = top_p ->next;
    delete tmp;
    return x;
 }
template <class elemType>
elemType linkStack<elemType>::top() const
{
         return top_p ->data;
}
template <class elemType>
bool linkStack<elemType>::isEmpty() const
{
      return top_p == NULL;
}
struct Node{//二叉树节点
    Node(const char d='#'):data(d), left(NULL), right(NULL) {};
    char data;
    Node* left;
    Node* right;
};
struct StNode{
     Node *node;
     int TimesPop;
     StNode ( Node *N = NULL ):node(N), TimesPop(0) {  }
};
//根据先序遍历构建一棵二叉树，返回root指针
Node* constructBinaryTree(const string& preOrder, unsigned& index){
    if (preOrder.size() == 0 || index == preOrder.size() || preOrder[index] == '#')//若空串或者index超出范围，则返回空指针
        return NULL;
    Node* T = new Node(preOrder[index++]);
    T->left = constructBinaryTree(preOrder, index);
    T->right = constructBinaryTree(preOrder, ++index);
    return T;
}

int maxDepth(Node* root) {
        if(root == NULL)
            return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
void postOrder(Node *root,int maxdepth)
{
 	linkStack< StNode > s;
    bool flag=true;
	StNode current(root);
    char result[maxdepth];
	s.push(current);
while (!s.isEmpty()&&flag)
   {  current = s.pop();
      if ( ++current.TimesPop == 3 )
           {   if(s.stacksize()==maxdepth-1)
               { result[0]=current.node->data;
                 for(int i=1;i<maxdepth;i++)
                 {
                     result[i]=s.pop().node->data;
                 }
                 flag=false;
                 for(int k=maxdepth-1;k>-1;k--){cout<<result[k];}
                  }
              continue;}
      s.push( current );
      if ( current.TimesPop == 1 )
            { if ( current.node->left != NULL )
            	s.push(StNode( current.node->left) );
	        }
         else {
	         if ( current.node ->right != NULL )
          		s.push(StNode( current.node->right ) );
	   }
  }
}

int main()
{
    string str;
    getline(cin,str);
    unsigned index = 0;
    Node *root = constructBinaryTree(str, index);
    int maxdepth=maxDepth(root);
    cout << maxdepth<<endl;
    postOrder(root,maxdepth);
    return 0;
}
