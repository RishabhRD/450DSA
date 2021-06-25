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


void make_bst(const vector<int>& nums, const int low, const int high, vector<int>& vec){
  if(low > high) return;
  const int mid = (low + high) / 2;
  vec.push_back(nums[mid]);
  make_bst(nums, low, mid - 1, vec);
  make_bst(nums, mid + 1, high, vec);
}

vector<int> sortedArrayToBST(vector<int> &nums) {
  vector<int> ans;
  make_bst(nums, 0, nums.size() - 1, ans);
  return ans;
}

void fill_nums(Node* root, vector<int>& nums){
  if(root == nullptr) return;
  fill_nums(root->left, nums);
  nums.push_back(root->data);
  fill_nums(root->right, nums);
}

Node* make_bst(const vector<int>& nums, const int low, const int high){
  if(low > high) return nullptr;
  const int mid = (low + high) / 2;
  Node* new_node = new Node{nums[mid]};
  new_node->left = make_bst(nums, low, mid - 1);
  new_node->right = make_bst(nums, mid + 1, high);
  return new_node;
}

Node* buildBalancedTree(Node* root) {
  vector<int> nums;
  fill_nums(root, nums);
  return make_bst(nums, 0, nums.size() - 1);
}
