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
  Node(int key) : data(key), left(nullptr), right(nullptr){
  }
};


void insert(Node*& root,const int key, Node*& succ){
  if(root == nullptr){
    root = new Node{key};
    return;
  }
  if(key < root->data){
    succ = root;
    insert(root->left, key, succ);
  }else{
    insert(root->right, key, succ);
  }
}

void replace(vector<int>& vec){
  const auto size = vec.size();
  Node* root = nullptr;
  for(int i = size - 1; i >= 0; i--){
    Node* succ = nullptr;
    insert(root, vec[i], succ);
    if(succ != nullptr){
      vec[i] = succ->data;
    }else{
      vec[i] = -1;
    }
  }
}
