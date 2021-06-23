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

int find_largest(Node* root, unordered_map<Node*, int>& mp){
  if(root == nullptr) return 0;
  if(mp.find(root) != mp.end()){
    return mp[root];
  }
  int including_current = root->data;
  if(root->left){
    including_current += find_largest(root->left->left, mp) + find_largest(root->left->right, mp);
  }
  if(root->right){
    including_current += find_largest(root->right->left, mp) + find_largest(root->right->right, mp);
  }
  int not_including_current = find_largest(root->left,mp) + find_largest(root->right, mp);
  mp[root] = max(including_current, not_including_current);
  return mp[root];
}

int getMaxSum(Node *root) {
  unordered_map<Node*, int> mp;
  return find_largest(root, mp);
}
