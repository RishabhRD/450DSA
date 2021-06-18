#include <queue>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
};
vector<int> reverseLevelOrder(Node *root)
{
  vector<int> vec;
  if(root == nullptr){
    return vec;
  }

  stack<int> st;
  queue<Node*> q;

  q.push(root);

  while(!q.empty()){
    Node* nd = q.front();
    q.pop();
    st.push(nd->data);
    if(nd->right)
      q.push(nd->right);
    if(nd->left)
      q.push(nd->left);
  }

  while(!st.empty()){
    vec.push_back(st.top());
    st.pop();
  }
  return vec;

}
