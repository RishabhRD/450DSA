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

Node* merge_bst(Node* root1, Node* root2){
  vector<int> nums1;
  fill_nums(root1, nums1);
  vector<int> nums2;
  fill_nums(root2, nums2);
  vector<int> nums;
  merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), back_inserter(nums));
  return make_bst(nums, 0, nums.size() - 1);
}
