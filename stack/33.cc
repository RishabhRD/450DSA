#include <queue>
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

struct Node
{
    struct Node *left, *right;
    int data;
};

auto pop(queue<Node*> q){
  auto nd = q.front();
  q.pop();
  return nd;
}
  
// Returns true if trees with root1 and root2
// are level by level anagram, else returns false.
bool areAnagrams(Node *root1, Node *root2){
  if(root1 == nullptr and root2 == nullptr) return true;
  if(roo1 == nullptr or root2 == nullptr) return false;
  queue<Node*> q1, q2;
  q1.push(root1);
  q2.push(root2);
  while(1){
    const int n1 = q1.size();
    const int n2 = q2.size();
    if(n1 != n2){
      return false;
    }
    if(n1 == 0) return false;
    vector<int> vec1, vec2;
    while(n1--){
      auto nd = pop(q1);
      vec1.push_back(nd->data);
      if(nd->left){
        q1.push(nd->left);
      }
      if(nd->right){
        q1.push(nd->right);
      }
      nd = pop(q2);
      vec2.push_back(nd->data);
      if(nd->left){
        q2.push(nd->left);
      }
      if(nd->right){
        q2.push(nd->right);
      }
    }
    sort(begin(vec1), end(vec1));
    sort(begin(vec2), end(vec2));
    if(vec1 != vec2){
      return false;
    }
  }
  return true;
}
