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

void fill_prev_map(Node* root, unordered_map<Node*, Node*>& prev_map){
  if(root->left){
    prev_map[root->left] = root;
    fill_prev_map(root->left, prev_map);
  }
  if(root->right){
    prev_map[root->right] = root;
    fill_prev_map(root->right, prev_map);
  }
}

list<Node*> get_path(Node* cur, unordered_map<Node*, Node*>& prev_map){
  list<Node*> path;
  while(cur != nullptr){
    path.push_front(cur);
    cur = prev_map[cur];
  }
  return path;
}

Node* get_node(int n, Node* root){
  if(root == nullptr) return nullptr;
  if(n == root->data){
    return root;
  }
  auto ln = get_node(n, root->left);
  if(ln != nullptr) return ln;
  auto rn = get_node(n, root->right);
  if(rn != nullptr) return rn;
  return nullptr;
}

Node *lca(Node *root, int n1, int n2) {
  unordered_map<Node*, Node*> prev_map;
  prev_map[root] = nullptr;
  fill_prev_map(root, prev_map);
  auto node1 = get_node(n1, root);
  auto node2 = get_node(n2, root);
  auto n1_path = get_path(node1, prev_map);
  auto n2_path = get_path(node2, prev_map);
  auto itr1 = n1_path.begin();
  auto itr2 = n2_path.begin();
  Node* val = root;
  while(itr1 != n1_path.end() || itr2 != n2_path.end()){
    if(*itr1 != *itr2){
      break;
    }else{
      val = *itr1;
    }
    itr1++;
    itr2++;
  }
  return val;
}

Node *lca(Node *root, int n1, int n2) {
  if(root == nullptr) return nullptr;
  if(root->data == n1 || root->data == n2){
    return root;
  }

  auto left = lca(root->left, n1, n2);
  auto right = lca(root->right, n1, n2);

  if(left && right){
    return root;
  }

  if(left == nullptr){
    return right;
  }else{
    return left;
  }
}
