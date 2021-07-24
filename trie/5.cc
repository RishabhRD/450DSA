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

struct trie_node{
  array<trie_node*, 2> children;
  bool is_leaf;
};

bool contains(trie_node* root, int num){
  return root->children[num] != nullptr;
}

trie_node*& get_node(trie_node* root, int num){
  return root->children[num];
}

void init(trie_node* root){
  root->children[0] = nullptr;
  root->children[1] = nullptr;
  root->is_leaf = false;
}

template <typename Iter>
bool insert(trie_node* root, Iter begin, Iter end){
  bool inserted = false;
  auto cur_node = root;
  for(auto cur = begin; cur != end; cur++){
    const auto cur_num = *cur;
    if(not contains(cur_node, cur_num)){
      auto& child_node = get_node(cur_node, cur_num);
      child_node = new trie_node{};
      init(child_node);
      inserted = true;
    }
    cur_node = get_node(cur_node, cur_num);
  }
  cur_node->is_leaf = true;
  return inserted;
}

vector<vector<int>> uniqueRow(int M[MAX][MAX],int row,int col) {
  vector<vector<int>> ret_vector;
  trie_node* root = new trie_node{};
  init(root);
  for(int i = 0; i < row; i++){
    vector<int> new_vector;
    for(int j = 0; j < col; j++){
      new_vector.push_back(M[i][j]);
    }
    if(insert(root, cbegin(new_vector), cend(new_vector))){
      ret_vector.push_back(std::move(new_vector));
    }
  }
  return ret_vector;
}

