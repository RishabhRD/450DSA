#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
};

void inorder(Node* n){
  if(n == nullptr) return;
  inorder(n->left);
  cout << n->data << "\n";
  inorder(n->right);
}

void inorder_iterative(Node* n){
  stack<Node*> st;
  Node* cur = n;
  while(!st.empty() || cur != nullptr){
    if(cur != nullptr){
      st.push(cur);
      cur = cur->left;
    }else{
      cur = st.top();
      st.pop();
      cout << cur->data << endl;
      cur = cur->right;
    }
  }
}
