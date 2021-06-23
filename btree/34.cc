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

bool isIsomorphic(Node *root1, Node *root2) {
  if(root1 == nullptr && root2 != nullptr) return false;
  if(root2 == nullptr && root1 != nullptr) return false;
  if(root1 == nullptr && root2 == nullptr) return true;
  if(root1->data != root2->data) return false;
  bool iso = isIsomorphic(root1->left, root2->left) &&
    isIsomorphic(root1->right, root2->right);
  if(iso) return true;
  iso = isIsomorphic(root1->left, root2->right) && isIsomorphic(root1->right, root2->left);
  return iso;
}
