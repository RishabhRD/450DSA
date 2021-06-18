#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct Node {
  int data;
  struct Node *left;
  struct Node *right;

  Node(int x) {
    data = x;
    left = right = nullptr;
  }
};

vector<int> levelOrder(Node *node) {
  vector<int> vec;
  if(node == nullptr) return vec;
  queue<Node*> q;
  q.push(node);
  while(!q.empty()){
    Node* nd = q.front();
    vec.push_back(nd->data);
    q.pop();
    if(nd->left)
      q.push(nd->left);
    if(nd->right)
      q.push(nd->right);
  }
  return vec;
}

int main(int argc, const char** argv) {
    return 0;
}
