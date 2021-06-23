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

int get_sum(Node* root, int& path_sum){
  if(root == nullptr){
    return 0;
  }
  int ls = 0, rs = 0, lh = 0, rh = 0;
  lh = get_sum(root->left, ls);
  rh = get_sum(root->right, rs);
  if(lh > rh){
    path_sum = root->data + ls;
    return 1 + lh;
  }else{
    path_sum = root->data + rs;
    return 1 + rh;
  }
}

int sumOfLongRootToLeafPath(Node *root) {
  if(root == nullptr) return 0;
  int path_sum = 0;
  get_sum(root, path_sum);
  return path_sum;
}
