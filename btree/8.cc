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

vector<int> leftView(Node *root) {
  vector<int> vec;
  if(root == nullptr) return vec;
  queue<Node*> q;
  q.push(root);
  while(!q.empty()){
    int n = q.size();
    for(int i = 0; i < n; i++){
      Node* tmp = q.front();
      q.pop();
      if(i == 0){
        vec.push_back(tmp->data);
      }
      if(tmp->left){
        q.push(tmp->left);
      }
      if(tmp->right){
        q.push(tmp->right);
      }
    }
  }
  return vec;
}
