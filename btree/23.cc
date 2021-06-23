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

bool same_tree(Node* first, Node* second){
  if(first == nullptr && second == nullptr) return true;
  else if(first == nullptr && second != nullptr) return false;
  else if(first != nullptr && second == nullptr) return false;
  return first->data == second->data && (same_tree(first->left, second->left)) && (same_tree(first->right, second->right));
}

bool dupSub(Node *first, Node* second) {
  if(first == nullptr) return false;
  if(second == nullptr) return false;
  if(same_tree(first, second) && (first->left || first->right)){
    return true;
  }
  return dupSub(first, second->left) ||
    dupSub(first, second->right) ||
    dupSub(first->left, second) ||
    dupSub(first->right, second);
}

bool dupSub(Node *root) {
  return dupSub(root->left, root->right);
}
