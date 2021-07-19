#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
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

class Node {
public:
  int val;
  vector<Node *> neighbors;
  Node() {
    val = 0;
    neighbors = vector<Node *>();
  }
  Node(int _val) {
    val = _val;
    neighbors = vector<Node *>();
  }
  Node(int _val, vector<Node *> _neighbors) {
    val = _val;
    neighbors = _neighbors;
  }
};

class Solution {
  unordered_set<Node *> visited;
  unordered_map<Node *, Node *> new_node_map;

  void visit(Node *cur) { visited.insert(cur); }

  bool is_visited(Node *cur) { return visited.find(cur) != visited.end(); }

  void add_mapping(Node *old, Node *node) { new_node_map[old] = node; }

  Node *get_new_node(Node *old) { return new_node_map[old]; }

  void dfs(Node *cur_node, Node *new_node) {
    visit(cur_node);
    add_mapping(cur_node, new_node);
    for (Node *neigh : cur_node->neighbors) {
      Node *new_neigh =
          (not is_visited(neigh)) ? new Node(neigh->val) : get_new_node(neigh);
      new_node->neighbors.push_back(new_neigh);
      if(not is_visited(neigh))
        dfs(neigh, new_neigh);
    }
  }

public:
  Node *cloneGraph(Node *node) {
    if(node == nullptr) return nullptr;
    Node *new_node = new Node(node->val);
    dfs(node, new_node);
    return new_node;
  }
};
