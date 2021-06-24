#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
  Node* next;
};

void push(vector<Node*>& vec, Node* node){
  if(vec.size() != 0){
    vec.back()->next = node;
  }
  vec.push_back(node);
}

void inorder(Node* root, vector<Node*>& vec){
  if(root == nullptr) return;
  inorder(root->left, vec);
  push(vec, root);
  inorder(root->right, vec);
}

void inorder(Node* root, Node*& prev){
  if(root == nullptr) return;
  inorder(root->left, prev);
  if(prev != nullptr){
    prev->next = root;
  }
  prev = root;
  inorder(root->right, prev);
}

void populateNext(Node *root) {
  Node* prev = nullptr;
  inorder(root, prev);
}
