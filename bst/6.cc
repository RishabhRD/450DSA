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

Node* LCA(Node *root, int n1, int n2) {
   //Your code here
  if(root == nullptr) return nullptr;
  if((n1 < root->data && n2 > root->data) || (n1 > root->data && n2 < root->data)){
    return root;
  }else if(n1 > root->data && n2 > root->data){
    return LCA(root->right, n1, n2);
  }else if(n1 < root->data && n2 < root->data){
    return LCA(root->left, n1, n2);
  }else{
    return root;
  }
}
