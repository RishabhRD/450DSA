#include <iostream>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct Node {
  int key;
  Node *left;
  Node *right;
};

Node* search(Node* root, int x){
  if(root == nullptr) return nullptr;
  if(root->key == x) return root;
  if(x < root->key) return search(root->left, x);
  return search(root->right, x);
}

Node* minimum(Node* root){
  while(root->left){
    root = root->left;
  }
  return root;
}

Node* parent_successor(Node* root, int key){
  Node* succ = nullptr;
  while(root != nullptr){
    if(key < root->key){
      succ = root;
      root = root->left;
    }else if(key > root->key){
      root = root->right;
    }else{
      break;
    }
  }
  return succ;
}

Node* successor(Node* root, Node* node){
  if(node->right){
    return minimum(node->right);
  }
  return parent_successor(root, node->key);
}

Node* maximum(Node* root){
  while(root->right){
    root = root->right;
  }
  return root;
}

Node* parent_predecessor(Node* root, int key){
  Node* pred = nullptr;
  while(root != nullptr){
    if(key < root->key){
      root = root->left;
    }else if(key > root->key){
      pred = root;
      root = root->right;
    }else break;
  }
  return pred;
}

Node* predecessor(Node* root, Node* node){
  if(node->left){
    return maximum(node->left);
  }
  return parent_predecessor(root, node->key);
}

void findPreSuc(Node* root, Node*& pre, Node*& suc, int key) {
  auto node = search(root, key);
  if(node == nullptr){
    pre = parent_predecessor(root, key);
    suc = parent_successor(root, key);
  }else{
    suc = successor(root, node);
    pre = predecessor(root, node);
  }
}
