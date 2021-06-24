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

bool search(Node* root, int x) {
  if(root == nullptr) return false;
  if(x == root->data) return true;
  if(x < root->data) return search(root->left, x);
  return search(root->right, x);
}
