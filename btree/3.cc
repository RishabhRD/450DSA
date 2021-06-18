#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
};

int height(struct Node *node) {
  if (node == nullptr)
    return 0;
  return 1 + max(height(node->left), height(node->right));
}

int diameter(Node *root) {
  if(root == nullptr) return 0;
  else return max({height(root->left) + height(root->right) + 1,
      diameter(root->left), diameter(root->right)});
}
