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

int minValue(Node* root) {
  if(root == nullptr){
    return -1;
  }
  while(root->left){
    root = root->left;
  }
  return root->data;
}
