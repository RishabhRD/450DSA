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

int largest_subtree(Node* root){
  if(root == nullptr) return 0;
  int ls = largest_subtree(root->left);
  int rs = largest_subtree(root->right);
  return max({ls, rs, root->data + ls + rs});
}
