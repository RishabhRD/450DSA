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
  array<trie_node*, 26> children;
  size_t freq;
};

trie_node* new_trie_node(){
  trie_node* root = new trie_node{};
  for(auto& x : root->children){
    x = nullptr;
  }
  root->freq = 0;
  return root;
}

bool contains(trie_node* root, char c){
  return root->children[c - 'a'] != nullptr;
}

decltype(auto) get_child(trie_node* root, char c){
  return root->children[c - 'a'];
}

void insert(trie_node* root, const string& str){
  auto cur_node = root;
  for(const char c : str){
    cur_node->freq++;
    if(not contains(cur_node, c)){
      get_child(cur_node, c) = new_trie_node();
    }
    cur_node = get_child(cur_node, c);
  }
}

void recurse_trie(trie_node* root, string& cur_string, vector<string>& resultant_vector){
  if(root->freq == 1 or root->freq == 0){
    resultant_vector.push_back(cur_string);
    return;
  }
  for(size_t i = 0; i < 26u; i++){
    if(contains(root, i + 'a')){
      cur_string.push_back(i + 'a');
      recurse_trie(get_child(root, i + 'a'), cur_string, resultant_vector);
      cur_string.pop_back();
    }
  }
}

vector<string> find_prefix(const vector<string>& vec){
  trie_node* root = new_trie_node();
  for(const auto& s : vec){
    insert(root, s);
  }
  string cur_string;
  vector<string> resultant_vector;
  recurse_trie(root, cur_string, resultant_vector);
  return resultant_vector;
}

int main(int argc, const char** argv) {
  cout << find_prefix({"zebra", "dog", "duck", "dove"}) << endl;
    return 0;
}
