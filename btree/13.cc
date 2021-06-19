#include <cmath>
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

int height(Node* root, unordered_map<Node*, int>& mp){
  if(root == nullptr){
    return 0;
  }

  if(mp.find(root) != mp.end()){
    return mp[root];
  }

  mp[root] = max(height(root->left, mp) , height(root->right, mp)) + 1;
  return mp[root];
}


bool isBalanced(Node *root) {
  if(root == nullptr) return true;
  unordered_map<Node*, int> mp;
  bool balanced = true;
  queue<Node*> q;
  q.push(root);
  while(!q.empty()){
    root = q.front();
    q.pop();
    balanced = balanced && (abs(height(root->left, mp) - height(root->right, mp)) <= 1);
    if(!balanced) return false;
    if(root->left){
      q.push(root->left);
    }
    if(root->right){
      q.push(root->right);
    }
  }
  return balanced;
}

int main(int argc, const char** argv) {
  Node n1 = {0, nullptr, nullptr};
  Node n2 = {0, nullptr, nullptr};
  Node n3 = {0, nullptr, nullptr};
  Node n4 = {0, nullptr, nullptr};
  Node n5 = {0, nullptr, nullptr};
  n1.left = &n2;
  n1.right = &n3;
  n2.left = &n4;
  n2.right = &n5;
  cout << isBalanced(&n1) << endl;
    return 0;
}
