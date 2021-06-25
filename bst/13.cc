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
};

Node* search(Node* root, int k){
  if(root == nullptr) return nullptr;
  else if(k == root->data) return root;
  else if(k < root->data) return search(root->left, k);
  else return search(root->right, k);
}

int countPairs(Node* root1, Node* root2, int x) {
  if(root1 == nullptr) return 0;
  auto target = search(root2, x - root1->data);
  auto ans = 0;
  if(target != nullptr) ans++;
  return ans + countPairs(root1->left, root2, x) + countPairs(root1->right, root2, x);
}
