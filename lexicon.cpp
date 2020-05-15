#include <iostream>

using namespace std;

class lexicon {
  struct node {
      string word;
      int times;
      node *left, *right, *parent;
      node(const string &s, node *l, node *r, node *p) 
        : word(s), left(l), right(r), parent(p) {}
    };

    node *root;

    static void purge(node *t) {
      if(t != nullptr){
        purge(t->left);
        purge(t->right);
        delete t;
      }
    }
 public:
 lexicon()
 : root(nullptr){}
 ~lexicon(){
   purge(root);
 }


 void insert(const string &s);

 int lookup(const string &s) const;

 int depth(const string &s) const;
 
 void replace(const string &s1, const string &s2);

 friend ostream & operator << (ostream &out, const lexicon &l);
};
