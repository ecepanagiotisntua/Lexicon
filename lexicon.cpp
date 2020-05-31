#include <iostream>
#include <cstring>

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

   static node *help_look (node *n, const string &s) {  
        if (n == nullptr) { return nullptr; }  
        if (n->word == s) { return n; }  
        if (s < n->word) { return help_look(n->left, s); }  
        else { return help_look(n->right, s); }  
    } 

   int help_depth(node *root, const string &s, int level)const{
     if (root == nullptr) return 0;
     if (root->word == s) return level;
     int down_level = help_depth(root->left, s, level+1);
     if (down_level != 0) return down_level;
     down_level = help_depth(root -> right, s, level +1);
     return down_level;

   } 

    static node *insert (node *n, const string &s) {  
        if (n == nullptr) { return new node(s, nullptr, nullptr, nullptr); }  
        if (n->word == s) { n->times++; }  
        else if (s < n->word) { n->left = insert(n->left, s); }  
        else { n->right = insert(n->right, s);}  
        return n;  
    }  

    static ostream & display(ostream &out, node* t){
      if (t ==nullptr) return out;
      display(out, t->left);
      out<<t->word<< " "<< t->times<<endl;
      display(out, t->right);
      return out;
    }

     static node *remove (node *n, const string &s) {  
        if (n == nullptr) { return nullptr;}  
        else if (s < n->word) { n->left = remove(n->left, s); }  
        else if (s > n->word) { n->right = remove(n->right, s); }  
        else {  
            if (n->left == nullptr && n->right == nullptr) {  
                delete n;  
                n = nullptr;  
            }  
            else if (n->left == nullptr) {  
                node *temp = n;  
                n = n->right;  
                delete temp;  
            }  
            else if (n->right == nullptr) {  
                node *temp = n;  
                n = n->left;  
                delete temp;  
            }  
            else {  
                node *temp = findMax(n->left);  
                n->word = temp->word;  
                n->times = temp->times;  
                n->left = remove(n->left, temp->word);  
            }  
        }  
        return n;  
    }  
  
    static node *findMax (node *n) {  
        node *p = n;  
        while (p->right != nullptr) { p = p->right; }  
        return p;  
    }  

 public:
 lexicon()
 : root(nullptr){}

 ~lexicon(){
   purge(root);
 }


 void insert(const string &s){
   root = insert(root, s);
 }

 

 int lookup(const string &s) const{
  node *n = help_look(root, s);
  if (n== nullptr) return 0;
  return n->times;
 }

 
  void replace(const string &s1, const string &s2) {  
        node *n = help_look(root, s1);  
            if (n == nullptr) { return; }  
        int i = n->times;  
        root = remove(root, s1);  
        node *s = help_look(root, s2);  
        if (s == nullptr) {  
            root = insert(root, s2);  
            (help_look(root, s2))->times = i;  
        }  
        else { s->times += i; }  
    }  
 
 int depth(const string &s) const{
   return help_depth(root, s, 1);
 }
 
 friend ostream & operator << (ostream &out, const lexicon &l){
   
    return l.display(out, l.root);
 }
};


int main() {
 lexicon l;
 l.insert("the");
 l.insert("boy");
 l.insert("and");
 l.insert("the");
 l.insert("wolf");
 cout << "The word ’the’ is found " << l.lookup("the") << " time(s)" << endl;
 cout << "The word ’and’ is found at depth " << l.depth("and") << endl;
 cout << l;
 l.replace("boy", "wolf");
 cout << "After replacement:\n";
 cout << l;
 cout << "Now the word ’and’ is found at depth " << l.depth("and") << endl;
 }
