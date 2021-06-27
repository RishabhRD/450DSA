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

template <typename Func> int count_if(Node *root, Func &&pred) {
  int count = 0;
  morris_traversal(root, [&count, pred = std::forward<Func>(pred)](auto cur) {
    if (pred(cur)) {
      count++;
    }
  });
  return count;
}

int getCount(Node *root, int l, int h) {
  auto in_range = [&](Node *cur) { return cur->data >= l && cur->data <= h; };
  return count_if(root, in_range);
}

int get_count(Node* root, int l, int h){
  if(root == nullptr) return 0;
  if(root->data < l){
    return get_count(root->right, l, h);
  }else if(root->data > h){
    return get_count(root->left, l, h);
  }else{
    return 1 + get_count(root->left, l , h) + get_count(root->right, l, h);
  }
}
