#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct interval{
  int low;
  int high;
};

struct Node {
  int max;
  interval i;
  Node *left;
  Node *right;
};

bool overlap(const interval& t1, const interval& t2){
  return t1.low < t2.high && t2.low < t1.high;
}

bool overlap_tree(Node* root, const interval& t){
  if(root == nullptr) return false;
  if(overlap(t, root->i)){
    return true;
  }else if(root->left && root->left->max >= t.low){
    return overlap_tree(root->left, t);
  }else{
    return overlap_tree(root->right, t);
  }
}

void insert(Node*& root, const interval& i){
  if(root == nullptr) {
    root = new Node{i.high, i, nullptr, nullptr};
  }else if(i.low < root->i.low){
    insert(root->left, i);
  }else{
    insert(root->right, i);
  }
}

bool does_overlap(const vector<interval>& vec){
  Node* root = nullptr;
  for(const auto& in : vec){
    if(overlap_tree(root, in)){
      return true;
    }
    insert(root, in);
  }
  return false;
}
