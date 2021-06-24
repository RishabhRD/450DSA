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

Node* search(Node* root, int x){
  if(root == nullptr) return nullptr;
  if(root->data == x) return root;
  if(x < root->data) return search(root->left, x);
  return search(root->right, x);
}

Node* get_parent(Node* root, Node* target){
  Node* parent = nullptr;
  Node* cur = root;
  while(cur != nullptr){
    if(cur->data == target->data){
      return parent;
    }else if(target->data < cur->data){
      parent = cur;
      cur = cur->left;
    }else{
      parent = cur;
      cur = cur->right;
    }
  }
  return parent;
}

Node* get_successor(Node* root){
  auto cur = root->right;
  while(cur->left){
    cur = cur->left;
  }
  return cur;
}

void transplant(Node*& root, Node* u, Node* v){
  auto parent = get_parent(root, u);
  if(parent == nullptr){
    root = v;
  }else if(parent->left == u){
    parent->left = v;
  }else{
    parent->right = v;
  }
}

Node *deleteNode(Node *root,  int X) {
  auto node = search(root, X);
  if(node == nullptr) return root;
  if(node->left == nullptr){
    transplant(root, node, node->right);
  }else if(node->right == nullptr){
    transplant(root, node, node->left);
  }else{
    auto successor = get_successor(node);
    auto successor_parent = get_parent(root, successor);
    if(node != successor_parent){
      transplant(root, successor, successor->right);
      successor->right = node->right;
    }
    transplant(root, node, successor);
    successor->left = node->left;
  }
  return root;
}
