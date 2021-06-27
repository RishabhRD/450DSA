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

template <typename Func> void morris_traversal(Node *root, Func &&func) {
  auto cur = root;
  while (cur != nullptr) {
    if (cur->left == nullptr) {
      func(cur);
      cur = cur->right;
    } else {
      auto pre = cur->left;
      while (pre->right != nullptr && pre->right != cur) {
        pre = pre->right;
      }
      if (pre->right == nullptr) {
        pre->right = cur;
        cur = cur->left;
      } else {
        pre->right = nullptr;
        func(cur);
        cur = cur->right;
      }
    }
  }
}

int size(Node *root) {
  int count = 0;
  morris_traversal(root, [&](auto cur) { count++; });
  return count;
}

int k_ele(Node *root, int k) {
  int ans = 0;
  int count = 0;
  morris_traversal(root, [&](auto cur) {
    count++;
    if (count == k) {
      ans =  cur->data;
    }
  });
  return ans;
}

float findMedian(struct Node *root) {
  const int node_count = size(root);
  if (node_count % 2 == 0) {
    const int k = node_count / 2;
    const int kth = k_ele(root, k);
    const int koneth = k_ele(root, k + 1);
    return ((float)kth + koneth) / 2;
  } else {
    const int k = (node_count + 1) / 2;
    const int kth = k_ele(root, k);
    return kth;
  }
}
