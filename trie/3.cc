#include <iostream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>
#include <array>

using namespace std;

template <typename T> concept is_container = requires(T a) {
  a.begin();
  a.end();
};

template <is_container T>requires (!std::same_as<T, std::string>)
std::ostream &operator<<(std::ostream &os, const T &cont) {
  os << '{';
  for (const auto &x : cont) {
    os << x;
    os << ' ';
  }
  os << '}';
  return os;
}

void printMatrix(const is_container auto &cont) {
  for (const auto &x : cont) {
    cout << x;
    cout << '\n';
  }
}

template <typename T, std::size_t... Is>
constexpr std::array<T, sizeof...(Is)>
create_array(T value, std::index_sequence<Is...>) {
  return {{(static_cast<void>(Is), value)...}};
}

template <std::size_t N, typename T>
constexpr std::array<T, N> create_array(const T &value) {
  return create_array(value, std::make_index_sequence<N>());
}
template <typename T>
constexpr auto accessor(T& t){
  return [&](int i) -> typename T::reference{
    return t.at(i);
  };
}

template <typename T>
constexpr auto accessor(const T& t){
  return [&](int i){
    return t.at(i);
  };
}

template <typename T>
constexpr auto const_accessor(T& t){
  return [&](int i){
    return t.at(i);
  };
}

template <typename T>
constexpr auto matrix_accessor(T& t){
  return [&](int i, int j) -> typename T::value_type::reference{
    return t.at(i).at(j);
  };
}

template <typename T>
constexpr auto matrix_accessor(const T& t){
  return [&](int i, int j) {
    return t.at(i).at(j);
  };
}

template <typename T>
constexpr auto const_matrix_accessor(T& t){
  return [&](int i, int j) {
    return t.at(i).at(j);
  };
}

template <typename T>
using lmt = std::numeric_limits<T>;

template <typename T, std::size_t N>
constexpr std::size_t array_size(const T (&)[N]) noexcept{
  return N;
}

vector<vector<string> > Anagrams_sorted(vector<string>& string_list) {
  vector<pair<string, int>> sorted_words;
  for(size_t i = 0; i < string_list.size(); i++){
   string str = string_list[i];
   sort(begin(str), end(str));
   sorted_words.emplace_back(std::move(str), i);
  }
  sort(begin(sorted_words), end(sorted_words));
  vector<vector<string>> ret_vec;
  vector<string> cur_vec;
  cur_vec.push_back(string_list[sorted_words[0].second]);
  for(int i = 1; i < string_list.size(); i++){
    if(sorted_words[i].first == sorted_words[i - 1].first){
      cur_vec.push_back(string_list[sorted_words[i].second]);
    }else{
      ret_vec.push_back(cur_vec);
      cur_vec.resize(0);
      cur_vec.push_back(string_list[sorted_words[i].second]);
    }
  }
  ret_vec.push_back(cur_vec);
  return ret_vec;
}

struct trie_node{
  array<trie_node*, 26> children;
  bool is_leaf;
  vector<string> stored_strings;
};

trie_node* new_trie_node(){
  trie_node* root = new trie_node{};
  root->is_leaf = false;
  return root;
}

bool contains(trie_node* root, char c){
  return root->children[c - 'a'] != nullptr;
}

decltype(auto) get_child(trie_node* root, char c){
  return root->children[c - 'a'];
}

void insert(trie_node* root, const string& ele){
  string sorted_ele = ele;
  sort(begin(sorted_ele), end(sorted_ele));
  auto cur_node = root;
  for(const char c : sorted_ele){
    if(not contains(cur_node, c)){
      get_child(cur_node, c) = new_trie_node();
    }
    cur_node = get_child(cur_node, c);
  }
  cur_node->is_leaf = true;
  cur_node->stored_strings.push_back(ele);
}

void traverse_trie(trie_node* root, vector<vector<string>>& ret_vec){
  if(root->is_leaf){
    ret_vec.push_back(root->stored_strings);
  }
  for(size_t i = 0; i < 26u; i++){
    if(contains(root, i + 'a')){
      traverse_trie(get_child(root, i + 'a'), ret_vec);
    }
  }
}

vector<vector<string>> Anagrams(vector<string>& string_list) {
  vector<vector<string>> ret_vec;
  trie_node* root = new_trie_node();
  for(const auto& str : string_list){
    insert(root, str);
  }
  traverse_trie(root, ret_vec);
  return ret_vec;
}

int main(int argc, const char** argv) {
  vector<string> list{"act", "god", "cat", "dog", "tac"};
  printMatrix(Anagrams(list));
    return 0;
}
