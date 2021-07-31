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

void rotate_with_additional_space(vector<vector<int>> &matrix) {
  vector<vector<int>> other_matrix = matrix;
  const auto n = matrix.size();
  size_t fill_j = 0;
  for (size_t i = 0; i < n; i++) {
    size_t fill_i = n - 1;
    for (size_t j = 0; j < n; j++) {
      matrix[fill_i][fill_j] = other_matrix[i][j];
      fill_i--;
    }
    fill_j++;
  }
}

void rotate_group(int &a, int &b, int &c, int &d) {
  swap(a, c);
  swap(a, b);
  swap(c, d);
}

void rotate(vector<vector<int>> &matrix) {
  const auto n = matrix.size();
  for (size_t x = 0; x < n / 2; x++) {
    for (size_t y = x; y < n - x - 1; y++) {
      rotate_group(matrix[x][y], matrix[y][n - 1 -x],
                   matrix[n - 1 - x][n - 1 - y], matrix[n - 1 - y][x]);
    }
  }
}

int main(int argc, const char** argv) {
  vector<vector<int>> matrix = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };
  rotate(matrix);
  printMatrix(matrix);
    return 0;
}
