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


bool sum_tree(Node *root, int& sum) {
  if(root == nullptr) return true;
  if(root->left == nullptr && root->right == nullptr){
    sum = root->data;
    return true;
  }
  int lh = 0;
  int rh = 0;
  auto left = sum_tree(root->left, lh);
  if(!left) return false;
  auto right = sum_tree(root->right, rh);
  if(!right) return false;
  sum = lh + rh + root->data;
  return lh + rh == root->data;
}

bool isSumTree(Node *root) {
  int sum = 0;
  return sum_tree(root, sum);
}
