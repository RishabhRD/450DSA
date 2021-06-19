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

void postorder(Node* root){
  if(root == nullptr){
    return;
  }
  postorder(root->left);
  postorder(root->right);
  cout << root->data << endl;
}

void postorder_iterative(Node* root){
  if(root == nullptr){
    return;
  }

  stack<Node*> st;
  stack<int> data;
  Node* cur = root;
  st.push(cur);
  while(!st.empty()){
    Node* top = st.top();
    st.pop();
    data.push(top->data);
    if(cur->right){
      st.push(cur->right);
    }
    if(cur->left){
      st.push(cur->left);
    }
  }
  while(!data.empty()){
    cout << data.top() << endl;
    data.pop();
  }
}
