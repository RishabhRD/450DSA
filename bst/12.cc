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

void k_smallest(Node *root, int k, int &n, int &ans) {
  if (root == nullptr || n >= k) {
    return;
  }
  k_smallest(root->left, k, n, ans);
  n++;
  if (n == k) {
    ans = root->data;
    return;
  }
  k_smallest(root->right, k, n, ans);
}

int kth_smallest(Node *root, int K) {
  int ans = -1;
  int n = 0;
  k_smallest(root, K, n, ans);
  return ans;
}

int KthSmallestElement(Node *root, int K) {
  int count = 0;
  Node *ans = nullptr;
  auto cur = root;
  while (cur != nullptr) {
    if (cur->left == nullptr) {
      count++;
      if (count == K) {
        ans = cur;
      }
      cur = cur->right;
    } else {
      auto pre = cur->left;
      while(pre->right != nullptr && pre->right != cur){
        pre = pre->right;
      }
      if(pre->right == nullptr){
        pre->right = cur;
        cur = cur->left;
      }else{
        pre->right = nullptr;
        count++;
        if(count == K) ans = cur;
        cur = cur->right;
      }
    }
  }
  if(ans != nullptr)
    return ans->data;
  return -1;
}
