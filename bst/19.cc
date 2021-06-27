#include <unordered_set>
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
  Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

bool is_leaf(Node* root){
  return root->left == nullptr and root->right == nullptr;
}

void fill_ele(unordered_set<int>& all_nodes, vector<int>& leaves, Node* root){
  if(root == nullptr) return;
  fill_ele(all_nodes, leaves, root->left);
  all_nodes.insert(root->data);
  if(is_leaf(root))
    leaves.push_back(root->data);
  fill_ele(all_nodes, leaves, root->right);
}

bool isDeadEnd(Node *root) {
  unordered_set<int> all_nodes;
  vector<int> leaves;
  fill_ele(all_nodes, leaves, root);
  all_nodes.insert(0);

  auto contains = [&](int i){
    return all_nodes.find(i) != all_nodes.end();
  };

  for(auto x : leaves){
    if(contains(x + 1) and contains(x - 1)) return true;
  }
  return false;
}
