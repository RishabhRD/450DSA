#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
};

inline bool is_leaf(Node* root){
  return (root->left == nullptr && root->right == nullptr);
}

bool check(Node *root) {
  if(root == nullptr){
    return true;
  }
  queue<Node*> q;
  q.push(root);
  bool leaf_found = false;
  while(!q.empty()){
    int size = q.size();
    for(int i = 0; i < size; i++){
      Node* node = q.front();
      q.pop();
      if(is_leaf(node)){
        leaf_found = true;
      }
      if(node->left){
        q.push(node->left);
      }
      if(node->right){
        q.push(node->right);
      }
    }
    if(leaf_found && !q.empty()){
      return false;
    }
  }
  return true;
}

int max_depth(Node* root){
  if(root == nullptr) return 0;
  return 1 + max(max_depth(root->left), max_depth(root->right));
}

int min_depth(Node* root){
  if(root == nullptr) return INT_MAX;
  if(root->left == nullptr && root->right == nullptr) return 1;
  return 1 + min(min_depth(root->left), min_depth(root->right));
}

bool check(Node* root){
  return max_depth(root) == min_depth(root);
}
