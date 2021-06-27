#include <unordered_set>
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
  Node(int x) : data(x), left(nullptr), right(nullptr) {}
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

auto to_sorted_list(Node* root){
  vector<int> vec;
  auto put_to_list = [&](auto cur){
    vec.push_back(cur->data);
  };
  morris_traversal(root, put_to_list);
  return vec;
}
