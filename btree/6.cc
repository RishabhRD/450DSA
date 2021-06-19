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

void preorder(Node* root){
  if(root == nullptr){
    return;
  }
  cout << root->data << endl;
  preorder(root->left);
  preorder(root->right);
}

void preorder_iterative(Node* root){
  if(root == nullptr){
    return;
  }

  stack<Node*> st;
  Node* cur = root;
  st.push(cur);
  while(!st.empty()){
    Node* top = st.top();
    st.pop();
    cout << top->data << endl;
    if(cur->right){
      st.push(cur->right);
    }
    if(cur->left){
      st.push(cur->left);
    }
  }
}
