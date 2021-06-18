#include <queue>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
};

int height(struct Node* node) {
  if(node == nullptr) return 0;
  return 1 + max(height(node->left), height(node->right));
}
