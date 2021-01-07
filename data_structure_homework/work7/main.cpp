#include <iostream>
#include<string>
#include <stdlib.h>
using namespace std;
template <class KEY, class OTHER>
struct SET {
    KEY key;
    OTHER other;
};

template <class KEY, class OTHER>
class dynamicSearchTable {
public:
    virtual SET<KEY, OTHER> *find(const KEY &x) const = 0;
    virtual void insert(const SET<KEY, OTHER> &x) = 0;

    virtual ~dynamicSearchTable() {};
};
template <class KEY, class OTHER>
class BinarySearchTree: public dynamicSearchTable<KEY, OTHER>
{ private:
    struct BinaryNode
    {
          SET<KEY, OTHER> data;
          BinaryNode *left;
          BinaryNode *right;
          BinaryNode( const SET<KEY, OTHER> & thedata,
                               BinaryNode *lt=NULL,  BinaryNode *rt=NULL )
         : data( thedata ), left( lt ), right( rt ) { }
    };
   BinaryNode *root;
public:
    BinarySearchTree() ;
    ~BinarySearchTree();
    SET<KEY, OTHER> *find(const KEY &x) const ;
    void print(const KEY &x) const ;
    void insert( const SET<KEY, OTHER> & x );

 private:
    void insert( const SET<KEY, OTHER> & x, BinaryNode * & t );
    void print(const KEY &x, BinaryNode *t ) const;
    SET<KEY, OTHER> *find(const KEY &x, BinaryNode *t ) const;
    void makeEmpty( BinaryNode *t );
};
template <class KEY, class OTHER>
SET<KEY, OTHER> * BinarySearchTree<KEY, OTHER>::find(
                                        const KEY &x ) const
{      return find( x, root );     }
template <class KEY, class OTHER>
SET<KEY, OTHER> *BinarySearchTree<KEY, OTHER>::find(
                                         const KEY & x, BinaryNode *t ) const
{     if  ( t == NULL  )
           return (SET<KEY, OTHER> *) t;
      while(t!=NULL)
      {
          if(t->data.key==x) return (SET<KEY, OTHER> *) t;
            else if(t->data.key>x) t=t->left;
                else t=t->right;
      }

}
template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::print(
                                        const KEY &x ) const
{      print( x, root );     }
template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::print(
                                         const KEY & x, BinaryNode *t ) const
{
      while(t!=NULL)
      {   cout<<t->data.key<<' ';
          if(t->data.key==x) break ;
            else if(t->data.key>x) t=t->left;
                else t=t->right;
      }
}
template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::insert( const SET<KEY,
                                                 OTHER> & x )
{    insert( x, root );    }
template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::insert( const SET<KEY,
                                                          OTHER> & x, BinaryNode *&t )
{	    if( t == NULL )
		   t = new BinaryNode( x, NULL, NULL );
         else if( x.key < t->data.key )
		   insert( x, t->left );
	    else if( t->data.key < x.key )
		   insert( x, t->right );
}
template <class KEY, class OTHER>
BinarySearchTree<KEY, OTHER>::BinarySearchTree()
{
    root=NULL;
}
template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::makeEmpty( BinaryNode *t )
{
    if(t==NULL) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}
template <class KEY, class OTHER>
BinarySearchTree<KEY, OTHER>::~BinarySearchTree()
{
    makeEmpty(root);
}
int main()
{   int x;
    cin>>x;
    SET<int, char *> a[x];
    string s,s1;
    int n[x+1];
    n[0]=0;
    cin.ignore();
    getline(cin,s);
    n[x]=s.length();
    int k=0,j=1;
    while(k<s.length())
       {  if(s[k]!=' '){k++;}
          else{n[j]=k;j++;k++;}
        }
     for(int m=0;m<x;m++)
     {    s1=s.substr(n[m],n[m+1]);
         a[m].key=atoi(s1.c_str());
     }
     BinarySearchTree<int, char *>  tree;
     for (int i = 0; i < x; ++i) tree.insert(a[i]);
     int z;
    cin>>z;
    SET<int, char *> *p;
    p = tree.find(z);
    if(p){cout<<1<<endl;}
    else cout<<-1<<endl;
    tree.print(z);

    return 0;
}
