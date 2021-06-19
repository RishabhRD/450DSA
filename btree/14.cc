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

vector<int> diagonal(Node *root) {
  vector<int> vec;
  if(root == nullptr) return vec;
  map<int, vector<Node*>> mp;
  stack<pair<Node*, int>> q;
  q.push({root, 0});
  while(!q.empty()){
    const auto node_pair = q.top();
    q.pop();
    auto node = node_pair.first;
    auto dist = node_pair.second;
    mp[dist].push_back(node);
    if(node->right){
      q.push({node->right, dist});
    }
    if(node->left){
      q.push({node->left, dist + 1});
    }
  }
  for(const auto& pr : mp){
    const auto& inner_vec = pr.second;
    for(const auto node : inner_vec){
      vec.push_back(node->data);
    }
  }
  return vec;
}
