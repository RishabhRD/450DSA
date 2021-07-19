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

bool is_visitable(const vector<vector<char>> &grid, int i, int j) {
  const int m = grid.size();
  const int n = grid[0].size();
  return i >= 0 and j >= 0 and i < m and j < n and
         grid[i][j] == '1';
}

void visit(int i, int j, const vector<vector<char>> &grid,
           vector<vector<bool>> &visited) {
  const vector<pair<int, int>> moves{{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                     {1, 0},   {-1, 1}, {0, 1},  {1, 1}};
  queue<pair<int, int>> q;
  q.emplace(i, j);
  visited[i][j] = true;
  while(not q.empty()){
    const auto top = q.front();
    const int x = top.first;
    const int y = top.second;
    q.pop();
    for(const auto& incr : moves){
      const int new_x = x + incr.first;
      const int new_y = y + incr.second;
      if(is_visitable(grid, new_x, new_y)){
        if(not visited[new_x][new_y]){
          visited[new_x][new_y] = true;
          q.emplace(new_x, new_y);
        }
      }
    }
  }
}

int numIslands(const vector<vector<char>> &grid) {


  const int m = grid.size();
  const int n = grid[0].size();

  vector<vector<bool>> visited(m, vector<bool>(n));

  int num_island = 0;

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] != '0' and visited[i][j] == false) {
        num_island++;
        visit(i, j, grid, visited);
      }
    }
  }
  return num_island;
}

int main() {
  const vector<vector<char>> grid{
    {'0', '1'}, {'1', '0'}, {'1', '1'}, {'1', '0'}
  };
  cout << numIslands(grid) << endl;
    return 0;
}
