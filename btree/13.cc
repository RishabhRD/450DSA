#include <cmath>
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



bool isBalanced(Node *root, int& height) {
  if(root == nullptr) return true;
  int lh = 0;
  int rh = 0;
  if(!isBalanced(root->left, lh)){
    return false;
  }
  if(!isBalanced(root->right, rh)){
    return false;
  }
  height = max(lh, rh) + 1;
  if(abs(lh - rh) <= 1){
    return true;
  }else{
    return false;
  }
}

bool isBalanced(Node* root){
  int height = 0;
  return isBalanced(root, height);
}

int main(int argc, const char** argv) {
  Node n1 = {0, nullptr, nullptr};
  Node n2 = {0, nullptr, nullptr};
  Node n3 = {0, nullptr, nullptr};
  Node n4 = {0, nullptr, nullptr};
  Node n5 = {0, nullptr, nullptr};
  n1.left = &n2;
  n1.right = &n3;
  n2.left = &n4;
  n2.right = &n5;
  cout << isBalanced(&n1) << endl;
    return 0;
}
