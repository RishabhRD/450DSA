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

constexpr int left(int i){
  return 2 * i + 1;
}

constexpr int right(int i){
  return 2 * i + 2;
}

void get_inorder_tree(const vector<int>& tree, int cur, vector<int>& result){
  if(cur >= tree.size()){
    return;
  }
  get_inorder_tree(tree, left(cur), result);
  result.push_back(tree[cur]);
  get_inorder_tree(tree, right(cur), result);
}

int binary_search(const vector<int>& arr, int ele){
  int low = 0;
  int high = arr.size() - 1;
  while(low <= high){
    int mid = (low + high) / 2;
    if(arr[mid] == ele) return mid;
    else if(arr[mid] > ele) high = mid - 1;
    else low = mid + 1;
  }
  return -1;
}

int min_swaps(vector<int>& tree){
  vector<int> inorder_tree;
  get_inorder_tree(tree, 0, inorder_tree);
  sort(tree.begin(), tree.end());
  int num_swaps = 0;
  for(int i = 0; i < inorder_tree.size(); i++){
    int find_index = binary_search(tree, inorder_tree[i]);
    if(find_index != i){
      num_swaps++;
    }
  }
  return num_swaps;
}
