#include <iostream>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
};

vector <int> zigZagTraversal(Node* root) {
  vector<int> vec;
  if(root == nullptr) return vec;
  stack<Node*> current_level;
  stack<Node*> next_level;
  bool l2r = false;
  current_level.push(root);
  while(!current_level.empty()){
    auto tmp = current_level.top();
    current_level.pop();
    vec.push_back(tmp->data);
    if(l2r){
      if(tmp->left){
        next_level.push(tmp->left);
      }
      if(tmp->right){
        next_level.push(tmp->right);
      }
    }else{
      if(tmp->right){
        next_level.push(tmp->right);
      }
      if(tmp->left){
        next_level.push(tmp->left);
      }
    }
    if(current_level.empty()){
      l2r = !l2r;
      swap(current_level, next_level);
    }
  }
  return vec;
}
