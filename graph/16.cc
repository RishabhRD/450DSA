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

template <typename Iter, typename Element>
auto contains(Iter begin, Iter end, Element c){
  return find(begin, end, c) != end;
}

vector<vector<int>> create_graph(string dict[], int n, int k){
  vector<vector<int>> graph(k);
  for(int i = 0; i < n - 1; i++){
    const auto& s1 = dict[i];
    const auto& s2 = dict[i + 1];
    for(int j = 0; j < static_cast<int>(min(s1.size(), s2.size())); j++){
      if(s1[j] != s2[j]){
        graph[s1[j] - 'a'].push_back(s2[j] - 'a');
        break;
      }
    }
  }
  return graph;
}


template <typename Func>
void dfs(const vector<vector<int>>& graph, int cur, vector<bool>& visited, Func&& visit){
  visited[cur] = true;
  for(auto x : graph[cur]){
    if(not visited[x]){
      dfs(graph, x, visited, visit);
    }
  }
  visit(cur);
}

string topological_sort(const vector<vector<int>>& graph){
  const int n = graph.size();
  vector<bool> visited(graph.size());
  string sorted_str;
  auto push_to_str = [&](int c){
    sorted_str.push_back(c + 'a');
  };
  for(int i = 0; i < n; i++){
    if(not visited[i])
      dfs(graph, i, visited, push_to_str);
  }
  reverse(begin(sorted_str), end(sorted_str));
  return sorted_str;
}

string findOrder(string dict[], int n, int k) {
  const auto graph =  create_graph(dict, n, k);
  return topological_sort(graph);
}

int main() {
  string dict[] = {"baa","abcd","abca","cab","cad"};
  cout << findOrder(dict, size(dict), 4) << endl;
    return 0;
}
