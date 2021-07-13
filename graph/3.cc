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

bool detect_cycle(int cur, vector<int> adj[], vector<bool>& visited, vector<bool>& call_stack){
  visited[static_cast<size_t>(cur)] = true;
  call_stack[static_cast<size_t>(cur)] = true;
  for(const auto neighbor : adj[cur]){
    if(call_stack[static_cast<size_t>(neighbor)]){
      return true;
    }
    if(not visited[static_cast<size_t>(neighbor)]){
      if(detect_cycle(neighbor, adj, visited, call_stack)){
        return true;
      }
    }
  }
  call_stack[static_cast<size_t>(cur)] = false;
  return false;
}

bool isCyclic(int V, vector<int> adj[]) {
  vector<bool> visited(static_cast<size_t>(V));
  vector<bool> call_stack(static_cast<size_t>(V));
  for(int i = 0; i < V; i++){
    if(not visited[static_cast<size_t>(i)]){
      if(detect_cycle(i, adj, visited, call_stack)){
        return true;
      }
    }
  }
  return false;
}
