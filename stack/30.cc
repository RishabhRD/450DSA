#include <queue>
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

int orangesRotting(vector<vector<int>> &grid) {
  const int n = grid.size();
  const int m = grid[0].size();
  auto is_in_range = [&](int i, int j){
    return i >= 0 and j >= 0 and i < n and j < m;
  };
  struct node {
    int time;
    int x, y;
  };
  queue<node> q;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      if(grid[i][j] == 2){
        q.push({0, i, j});
      }
    }
  }
  auto push_to_queue = [&](int x, int y, int time){
    if(is_in_range(x, y)){
      if(grid[x][y] == 1){
        grid[x][y] = 2;
        q.push({time, x, y});
      }
    }
  };
  int max_time = 0;
  while(not q.empty()){
    const auto nd = q.front();
    max_time = max(max_time, nd.time);
    q.pop();
    const int x = nd.x;
    const int y = nd.y;
    const int new_time = nd.time + 1;
    push_to_queue(x + 1, y, new_time);
    push_to_queue(x, y + 1, new_time);
    push_to_queue(x - 1, y, new_time);
    push_to_queue(x, y - 1, new_time);
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      if(grid[i][j] == 1){
        return -1;
      }
    }
  }
  return max_time;
}

int main(int argc, const char** argv) {
  vector<vector<int>> grid = {
    {0,1,2},{0,1,2},{2,1,1}
  };
  cout << orangesRotting(grid) << endl;
    return 0;
}
