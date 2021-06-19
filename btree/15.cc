#include <cmath>
#include <unordered_set>
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

inline bool is_leaf(Node* root){
  return root->left == nullptr && root->right == nullptr;
}

void add_left(Node* root, vector<int>& cont){
  if(root == nullptr) return;
  if(root->left){
    cont.push_back(root->data);
    add_left(root->left, cont);
  }else if(root->right){
    cont.push_back(root->data);
    add_left(root->right, cont);
  }
}

void add_leaves(Node* root, vector<int>& cont){
  if(root == nullptr) return;
  add_leaves(root->left, cont);
  if(is_leaf(root)){
    cont.push_back(root->data);
  }
  add_leaves(root->right, cont);
}

void add_right(Node* root, vector<int>& cont){
  if(root == nullptr) return;
  if(root->right){
    add_right(root->right, cont);
    cont.push_back(root->data);
  }else if(root->left){
    add_right(root->left, cont);
    cont.push_back(root->data);
  }
}


vector <int> printBoundary(Node *root) {
  vector<int> cont;
  if(root == nullptr){
    return cont;
  }
  cont.push_back(root->data);
  add_left(root->left, cont);
  add_leaves(root->left, cont);
  add_leaves(root->right, cont);
  add_right(root->right, cont);
  return cont;
}

int main(int argc, const char** argv) {
  Node n1 = {1, nullptr, nullptr};
  Node n2 = {2, nullptr, nullptr};
  Node n3 = {3, nullptr, nullptr};
  n1.left = &n2;
  n1.right = &n3;
  vector<int> vec = printBoundary(&n1);
  for(auto x : vec){
    cout << x << " ";
  }
  cout << endl;
    return 0;
}
