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

Node* lca(Node* root, int a, int b){
  if(root == nullptr) return nullptr;
  if(root->data == a || root->data == b) return root;
  Node* ln = lca(root->left, a, b);
  Node* rn = lca(root->right, a, b);
  if(ln && rn){
    return root;
  }
  if(ln){
    return ln;
  }
  return rn;
}

int dist(Node* root, int x){
  if(root == nullptr) return -1;
  if(root->data == x){
    return 0;
  }
  int left_dist = dist(root->left, x);
  int right_dist = dist(root->right, x);
  if(left_dist == -1 && right_dist == -1){
    return -1;
  }else if(left_dist != -1 && right_dist != -1){
    return 1 + min(left_dist, right_dist);
  }else if(left_dist == -1 && right_dist != -1){
    return 1 + right_dist;
  }else{
    return 1 + left_dist;
  }
}

int findDist(Node* root, int a, int b) {
  root = lca(root, a, b);
  auto d1 = dist(root, a);
  auto d2 = dist(root, b);
  return d1 + d2;
}
