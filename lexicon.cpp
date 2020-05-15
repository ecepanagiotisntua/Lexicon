#include <iostream>

using namespace std;

class lexicon {
  struct node {
      string word;
      int times = 1;
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

    static bool insert(node *t, const T &x){
      if (x < t->word){
        if (t->left == nullptr){
          t->left = new node(x, nullptr, nullptr, t);
          return true;
        } else
          return insert(t->left, x);
      } else if (x > t->word){
        if (t->right == nullptr){
          t->right = new node(x, nullptr, nullptr, t);
          return true;
        } else
          return insert(t->right, x);

      }
     else if (x == t->word) t->times++;

    }

 public:
 lexicon()
 : root(nullptr){}
 ~lexicon(){
   purge(root);
 }


 void insert(const string &s){
   if (root == nullptr){
     root = new node(s, nullptr, nullptr, nullptr);
    }
    else if(insert(root, s));

 }

 

 int lookup(const string &s) const;

 int depth(const string &s) const;
 
 void replace(const string &s1, const string &s2);

 friend ostream & operator << (ostream &out, const lexicon &l);
};
