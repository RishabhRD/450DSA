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
  Node(int x) : data(x) , left(nullptr), right(nullptr){
  }
};

Node* insert(const vector<int>& vec, int& cur_index, int bound = INT32_MAX){
  if(cur_index == vec.size() || vec[cur_index] > bound){
    return nullptr;
  }
  Node* root = new Node{vec[cur_index]};
  cur_index++;
  root->left = insert(vec, cur_index, root->data);
  root->right = insert(vec, cur_index, bound);
  return root;
}

Node* constructTree(int pre[], int size) {
  vector<int> vec;
  std::copy(pre, pre + size, back_inserter(vec));
  int cur_index = 0;
  return insert(vec, cur_index); 
}
