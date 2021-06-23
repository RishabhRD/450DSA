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

void print(vector<int>& path, int j){
  for(int i = j ; i < path.size(); i++){
    cout << path[i] << " ";
  }
  cout << endl;
}

void print_paths(Node* root, vector<int>& path, int k){
  if(!root) return;
  path.push_back(root->data);
  print_paths(root->left, path, k);
  print_paths(root->right, path, k);

  int f = 0;
  for(int i = path.size() - 1; i >= 0; i--){
    f += path[i];
    if(f == k){
      print(path, i);
    }
  }
  path.pop_back();
}
