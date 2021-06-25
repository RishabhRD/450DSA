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
};

void k_largest(Node* root, int k, int& n, int& ans){
  if(root == nullptr || n >= k){
    return;
  }
  k_largest(root->right, k, n, ans);
  n++;
  if(k == n){
    ans = root->data;
    return;
  }
  k_largest(root->left, k, n, ans);
}

int kthLargest(Node *root, int K) {
  int ans = -1;
  int n = 0;
  k_largest(root, K, n, ans);
  return ans;
}
