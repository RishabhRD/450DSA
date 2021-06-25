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

void fill_inorder_vec(Node* root, vector<int>& vec){
  if(root == nullptr) return;
  fill_inorder_vec(root->left, vec);
  vec.push_back(root->data);
  fill_inorder_vec(root->right, vec);
}

void fill_node(Node* root, vector<int>& vec){
  if(root == nullptr) return;
  fill_node(root->left, vec);
  root->data = vec.back();
  vec.pop_back();
  fill_node(root->right, vec);
}

Node *binaryTreeToBST(Node *root) {
  vector<int> inorder_vec;
  fill_inorder_vec(root, inorder_vec);
  sort(inorder_vec.begin(), inorder_vec.end(), greater<int>());
  fill_node(root, inorder_vec);
  return root;
}

int main(int argc, const char** argv) {
  Node n1 = {14, nullptr, nullptr};
  Node n2 = {2, nullptr, nullptr};
  Node n3 = {5, nullptr, nullptr};
  n1.left = &n2;
  n1.right = &n3;
  auto root = binaryTreeToBST(&n1);
  cout << root->data << " " << root->left->data << " " << root->right->data << endl;
    return 0;
}
