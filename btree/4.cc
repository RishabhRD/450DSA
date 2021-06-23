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

void mirror(Node *node) {
  if(node == nullptr) return;
  swap(node->left, node->right);
  mirror(node->left);
  mirror(node->right);
}
