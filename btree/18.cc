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

int sum_tree(Node* root){
  if(root == nullptr){
    return 0;
  }
  int lsum = sum_tree(root->left);
  int rsum = sum_tree(root->right);
  int cur = root->data;
  root->data = lsum + rsum;
  return lsum + rsum + cur;
}

void toSumTree(Node *node) {
  sum_tree(node);
}
