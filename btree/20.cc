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

Node* buildTree(int* in, int* pre, int in_begin, int in_end, int pre_index){
  if(in_begin > in_end){
    return nullptr;
  }
  Node* root = new Node{pre[pre_index], nullptr, nullptr};
  int index = -1;
  for(int i = in_begin; i <= in_end; i++){
    if(in[i] == pre[pre_index]){
      index = i;
    }
  }
  root->left = buildTree(in, pre, in_begin, index - 1, pre_index + 1);
  root->right = buildTree(in, pre, index + 1, in_end, pre_index + index - in_begin + 1);
  return root;
}

Node *buildTree(int in[], int pre[], int n) {
  return buildTree(in, pre, 0, n - 1, 0);
}
