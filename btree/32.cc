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


void fill_prev_map(Node* root, unordered_map<int, int>& prev_map){
  if(root == nullptr) return;
  if(root->left){
    prev_map[root->left->data] = root->data;
    fill_prev_map(root->left, prev_map);
  }
  if(root->right){
    prev_map[root->right->data] = root->data;
    fill_prev_map(root->right, prev_map);
  }
}

unordered_map<int, int> get_prev_map(Node* root){
  unordered_map<int, int> prev_map;
  prev_map[root->data] = -1;
  fill_prev_map(root, prev_map);
  return prev_map;
}

int kthAncestor(Node *root, int k, int node) {
  auto prev_map = get_prev_map(root);
  for(int i = 0; i < k; i++){
    node = prev_map[node];
    if(node == -1) return -1;
  }
  return node;
}
