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

int minStepToReachTarget(vector<int> &knight_pos, vector<int> &target_pos,
                         int n) {
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
  vector<vector<bool>> visited(n + 1, vector<bool>(n + 1));
  vector<pair<int, int>> moves{{-1, -2}, {1, -2}, {-2, -1}, {2, -1},
                               {-2, 1},  {2, 1},  {-1, 2},  {1, 2}};
  queue<pair<int, int>> q;
  int cur_pos = 0;
  q.push({target_pos[0], target_pos[1]});
  visited[target_pos[1]][target_pos[1]] = true;
  while(not q.empty()){
    const int size = q.size();
    for(int i = 0; i < size; i++){
      const auto top = q.front();
      dp[top.first][top.second] = cur_pos;
      if(top.first == knight_pos[0] and top.second == knight_pos[1]) return cur_pos;
      q.pop();
      for(const auto& move : moves){
        const int new_x = move.first + top.first;
        const int new_y = move.second + top.second;
        if(new_x < 1 or new_y < 1 or new_x > n or new_y > n){
          continue;
        }
        if(visited[new_x][new_y]){
          continue;
        }
        q.push({new_x, new_y});
        visited[new_x][new_y] = true;
      }
    }
    cur_pos++;
  }
  return dp[knight_pos[0]][knight_pos[1]];
}

int main() {
  vector knight_pos =  {6, 1};
  vector target_pos = {2, 4};
  int n = 7;
  cout << minStepToReachTarget(knight_pos, target_pos, n) << endl;
  return 0;
}
