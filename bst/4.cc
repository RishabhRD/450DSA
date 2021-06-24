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
};

bool isBST(Node* root, int& cur_min, int& cur_max){
  if(root->left == nullptr && root->right == nullptr){
    cur_min = root->data;
    cur_max = root->data;
    return true;
  }

  int l_min = INT32_MAX;
  int r_min = INT32_MAX;
  int l_max = INT32_MIN;
  int r_max = INT32_MIN;

  if(root->left){
    if(!isBST(root->left, l_min, l_max)){
      return false;
    }
  }
  if(root->right){
    if(!isBST(root->right, r_min, r_max)){
      return false;
    }
  }
  cur_min = min({l_min, root->data, r_min});
  cur_max = max({l_max, root->data, r_max});
  return root->data > l_max && root->data < r_min;
}

bool isBST(Node *root) {
  int min = INT32_MAX;
  int max = INT32_MIN;
  return isBST(root, min, max);
}
