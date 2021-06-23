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

int largest_subtree(Node* root, int& max_sum){
  if(root == nullptr) return 0;
  int ls = largest_subtree(root->left, max_sum);
  int rs = largest_subtree(root->right, max_sum);
  return max(max_sum, root->data + ls + rs);
}
