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

vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc,
                              int newColor) {
  const int m = image.size();
  const int n = image[0].size();
  auto is_in_bound = [&](int x, int y){
    return x >= 0 and y >= 0 and x < m and y < n;
  };
  const int old = image[sr][sc];
  const vector<pair<int, int>> moves{{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
  vector visited(m, vector<bool>(n));
  queue<pair<int, int>> q;
  q.push({sr, sc});
  visited[sr][sc] = true;
  while(not q.empty()){
    auto [x, y] = q.front();
    q.pop();
    image[x][y] = newColor;
    for(const auto& [incr_x, incr_y] : moves){
      const int new_x = x + incr_x;
      const int new_y = y + incr_y;
      if(is_in_bound(new_x, new_y)){
        if(not visited[new_x][new_y] and image[new_x][new_y] == old){
          visited[new_x][new_y] = true;
          q.push({new_x, new_y});
        }
      }
    }
  }
  return image;
}
