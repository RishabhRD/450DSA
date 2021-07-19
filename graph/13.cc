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

vector<size_t> get_indegree(vector<vector<size_t>>& graph){
  const auto size = graph.size();
  vector<size_t> indegree_vec(size);;
  for(const auto& vec : graph){
    for(const auto x : vec){
      indegree_vec[x]++;
    }
  }
  return indegree_vec;
}

vector<size_t> job_timing(vector<vector<size_t>>& graph){
  vector<size_t> indegree_vec = get_indegree(graph);
  auto indegree =[&](size_t i) -> size_t&{
    return indegree_vec[i];
  };
  size_t n = graph.size();
  vector<size_t> time(n);
  queue<size_t> q;
  for(size_t i = 0; i < n; i++){
    if(indegree(i) == 0){
      q.push(i);
    }
  }
  while(not q.empty()){
    const auto top = q.front();
    q.pop();
    for(auto x : graph[top]){
      indegree(x)--;
      if(indegree(x) == 0){
        time[x] = time[top] + 1;
      }
    }
  }
  return time;
}
