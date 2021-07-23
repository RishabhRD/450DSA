#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>

using namespace std;

template <typename T>
concept is_container = requires(T a) {
  a.begin();
  a.end();
};

template <is_container T>
requires(!std::same_as<T, std::string>) std::ostream &
operator<<(std::ostream &os, const T &cont) {
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
template <typename T> constexpr auto accessor(T &t) {
  return [&](int i) -> typename T::reference { return t.at(i); };
}

template <typename T> constexpr auto accessor(const T &t) {
  return [&](int i) { return t.at(i); };
}

template <typename T> constexpr auto const_accessor(T &t) {
  return [&](int i) { return t.at(i); };
}

template <typename T> constexpr auto matrix_accessor(T &t) {
  return [&](int i, int j) ->
         typename T::value_type::reference { return t.at(i).at(j); };
}

template <typename T> constexpr auto matrix_accessor(const T &t) {
  return [&](int i, int j) { return t.at(i).at(j); };
}

template <typename T> constexpr auto const_matrix_accessor(T &t) {
  return [&](int i, int j) { return t.at(i).at(j); };
}

template <typename T> using lmt = std::numeric_limits<T>;

template <typename T, std::size_t N>
constexpr std::size_t array_size(const T (&)[N]) noexcept {
  return N;
}

struct TrieNode {
  TrieNode *children[26];
  bool isLeaf;
};

bool contains(TrieNode* root, char c){
  return root->children[c - 'a'] != nullptr;
}

TrieNode*& get_node(TrieNode* root, char c){
  return root->children[c - 'a'];
}

void init(TrieNode* root){
  for(int i = 0; i < 26; i++){
    root->children[i] = nullptr;
  }
  root->isLeaf = false;
}

void insert(struct TrieNode *root, string key) {
  const auto size = key.size();
  auto cur_node = root;
  for(size_t i = 0; i < size; i++){
    const char cur_char = key[i];
    if(not contains(cur_node, cur_char)){
      auto& new_trie_node = get_node(cur_node, cur_char);
      new_trie_node = new TrieNode{};
      init(new_trie_node);
      if(i == size - 1){
        new_trie_node->isLeaf = true;
      }
    }
    cur_node = get_node(cur_node, cur_char);
  }
}

// Function to use TRIE data structure and search the given string.
bool search(struct TrieNode *root, string key) {
  const auto size = key.size();
  auto cur_node = root;
  for(size_t i = 0; i < size; i++){
    const auto cur_char = key[i];
    if(not contains(cur_node, cur_char)){
      return false;
    }
    cur_node = get_node(cur_node, cur_char);
    if(i == size - 1){
      if(cur_node->isLeaf == false) return false;
    }
  }
  return true;
}
