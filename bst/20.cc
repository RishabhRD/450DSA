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

bool is_bst(Node* root, int& min_ele, int& max_ele, int& bst_size){
  if(root->left == nullptr && root->right == nullptr){
    bst_size = 1;
    min_ele = root->data;
    max_ele = root->data;
    return true;
  }
  int l_max = INT32_MIN;
  int r_max = INT32_MIN;
  int l_min = INT32_MAX;
  int r_min = INT32_MAX;
  int l_bst_size = 0;
  int r_bst_size = 0;
  bool l_bst = true;
  bool r_bst = true;
  if(root->left){
    l_bst = is_bst(root->left, l_min, l_max, l_bst_size);
  }
  if(root->right){
    r_bst = is_bst(root->right, r_min, r_max, r_bst_size);
  }
  min_ele = min({root->data, l_min, r_min});
  max_ele = max({root->data, l_max, r_max});
  bool bst_cond = root->data > l_max && root->data < r_min;
  if(l_bst && r_bst && bst_cond){
    bst_size =  l_bst_size + r_bst_size + 1;
  }else{
    bst_size = max(l_bst_size, r_bst_size);
  }
  return bst_cond && l_bst && r_bst;
}

int largestBst(Node *root) {
  if(root == nullptr) return 0;
  int min_ele = INT32_MAX;
  int max_ele = INT32_MIN;
  int bst_size = 0;
  is_bst(root, min_ele, max_ele, bst_size);
  return bst_size;
}

int main(int argc, const char** argv) {
  Node nodes[] = {4, 2, 5, 1};
  int size = sizeof(nodes) / sizeof(Node);
  auto pl = [&](int i, int j){
    nodes[i].left = nodes + j;
  };
  auto pr = [&](int i, int j){
    nodes[i].right = nodes + j;
  };
  pl(0, 1);
  pl(1, 3);
  pr(0, 2);
  cout << largestBst(nodes) << endl;
}
