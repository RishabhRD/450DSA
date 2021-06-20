#include <cmath>
#include <unordered_set>
#include <iostream>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
};

void add(Node*& root, char data){
  root = new Node{data - '0' , nullptr, nullptr};
}

void add_left(Node* root, char data){
  root->left = new Node{data - '0', nullptr, nullptr};
}

void add_right(Node* root, char data){
  root->right = new Node{data - '0', nullptr, nullptr};
}

pair<vector<vector<int>>, vector<vector<int>>> create_paren_map(const string& str){
  int max_levels = 0;
  int level = 0;
  for(const auto c : str){
    if(c == '('){
      max_levels = max(level, max_levels);
      level++;
    }else if(c == ')'){
      level--;
    }
  }
  level = 0;
  vector<vector<int>> opening_braces(max_levels + 1);
  vector<vector<int>> closing_braces(max_levels + 1);
  for(int i = 0; i != str.size(); i++){
    auto c = str[i];
    if(c == '('){
      opening_braces[level].push_back(i);
      level++;
    }else if(c == ')'){
      level--;
      closing_braces[level].push_back(i);
    }
  }
  return {opening_braces, closing_braces};
}

Node* create_tree(const string& str, const int begin, const int end, const int cur_level, const vector<vector<int>>& opening_braces, const vector<vector<int>>& closing_braces){
  Node* nd = new Node{str[begin] - '0', nullptr, nullptr};
  if(opening_braces[cur_level].size() == 1){
    int new_begin = opening_braces[cur_level][0] + 1;
    int new_end = closing_braces[cur_level][0] - 1;
    if(new_begin > begin && new_end < end)
      nd->left = create_tree(str, opening_braces[cur_level][0] + 1, closing_braces[cur_level][0] - 1, cur_level + 1, opening_braces, closing_braces);
  }else if(opening_braces[cur_level].size() == 2){
    int new_begin = opening_braces[cur_level][0] + 1;
    int new_end = closing_braces[cur_level][0] - 1;
    if(new_begin > begin && new_end < end)
      nd->left = create_tree(str, opening_braces[cur_level][0] + 1, closing_braces[cur_level][0] - 1, cur_level + 1, opening_braces, closing_braces);
    new_begin = opening_braces[cur_level][1] + 1;
    new_end = closing_braces[cur_level][1] - 1;
    if(new_begin > begin && new_end < end)
      nd->right = create_tree(str, opening_braces[cur_level][1] + 1, closing_braces[cur_level][1] - 1, cur_level + 1, opening_braces, closing_braces);
  }
  return nd;
}

void print(const vector<vector<int>>& braces){
  for(int i = 0; i < braces.size(); i++){
      const vector<int>& vec = braces[i];
    cout << "Level " << i << " : ";
    for(auto x : vec){
      cout << x << " " ;
    }
    cout << endl;
  }
}

Node* tree_from_string(const string& str){
  auto [opening_braces, closing_braces] = create_paren_map(str);
  return create_tree(str, 0, str.size() - 1, 0, opening_braces, closing_braces);
}

void print(Node* root){
  if(root == nullptr) return;
  cout << root->data << " : ";
  if(root->left){
    cout << root->left->data << " ";
  }
  if(root->right){
    cout << root->right->data << " ";
  }
  cout << endl;
  print(root->left);
  print(root->right);
}

int main(int argc, const char** argv) {
  string str = "1(2(3)(4))(2)";
  Node* root = tree_from_string(str);
  print(root);
    return 0;
}
