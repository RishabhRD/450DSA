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

vector<int> topView(Node *root) {
  vector<int> vec;
  if(root == nullptr) return vec;
  map<int, vector<Node*>> mp;
  queue<pair<Node*, int>> q;
  q.push({root, 0});
  while(!q.empty()){
    const auto node_pair = q.front();
    q.pop();
    auto node = node_pair.first;
    auto dist = node_pair.second;
    mp[dist].push_back(node);
    if(node->left){
      q.push({node->left, dist - 1});
    }
    if(node->right){
      q.push({node->right, dist + 1});
    }
  }
  for(const auto& pr : mp){
    vec.push_back(pr.second.front()->data);
  }
  return vec;
}
