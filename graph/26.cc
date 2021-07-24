#include <stack>
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

template <typename Graph>
void fill_order(int cur, const Graph& adj, vector<bool>& visited, stack<int>& st){
  visited[cur] = true;
  for(auto x : adj[cur]){
    if(not visited[x]){
      fill_order(x, adj, visited, st);
    }
  }
  st.push(cur);
}

template <typename Graph>
void dfs(int cur, const Graph& adj, vector<bool>& visited){
  visited[cur] = true;
  for(auto x : adj[cur]){
    if(not visited[x]){
      dfs(x, adj, visited);
    }
  }
}

template <typename Graph>
auto get_tranpose(const Graph& graph, int V){
  vector<vector<int>> new_graph(V);
  for(int i = 0; i < V; i++){
    for(auto x : graph[i]){
      new_graph[x].push_back(i);
    }
  }
  return new_graph;
}

int kosaraju(int V, vector<int> adj[]) {
  stack<int> st;
  vector<bool> visited(V);
  for(int i = 0; i < V; i++){
    if(not visited[i])
      fill_order(i, adj, visited, st);
  }

  const auto new_graph = get_tranpose(adj, V);

  fill(begin(visited), end(visited), false);

  int sum = 0;
  while(not st.empty()){
    const int top = st.top();
    st.pop();
    if(not visited[top]){
      sum++;
      dfs(top, new_graph, visited);
    }
  }
  return sum;
}