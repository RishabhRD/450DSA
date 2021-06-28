#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <tuple>
#include <unordered_map>
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

template <typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& pr){
  os << "{" << pr.first << " " << pr.second << "}";
  return os;
}

pair<int, int> dfs(int start, vector<bool> &visited,
                   unordered_map<int, pair<int, int>> &graph, int prev = -1) {
  visited[start] = true;
  if (graph.find(start) != graph.end()) {
    return dfs(graph[start].first, visited, graph, start);
  }
  return {graph[prev].first, graph[prev].second};
}

vector<vector<int>> solve(int n, int p, vector<int> a, vector<int> b,
                          vector<int> d) {
  unordered_map<int, pair<int, int>> graph;
  const int size = a.size();
  for (int i = 0; i < size; i++) {
    graph[a[i]] = {b[i], d[i]};
  }
  vector<bool> visited(n + 1);
  vector<vector<int>> ans;
  for (int i = 1; i < n; i++) {
    if(visited[i]){
      continue;
    }
    auto comp = dfs(i, visited, graph);
    if (comp.first == -1) {
      continue;
    }
    ans.push_back({i, comp.first, comp.second});
  }
  return ans;
}

int main(int argc, const char **argv) {
  vector<int> a = {1, 3, 2, 5};
  vector<int> b = {3, 4, 5, 6};
  vector<int> d = {69, 20, 40, 12};
  int n = 6;
  int p = a.size();
  printMatrix(solve(n, p, a, b, d));
  return 0;
}
