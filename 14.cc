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

int max_product(const vector<int> &vec) {
  const auto size = vec.size();
  if (size == 1)
    return vec[0];
  const int count_zero = accumulate(cbegin(vec), cend(vec), 0,
                                    [](int x, int y) { return x + (y == 0); });
  if(count_zero == size) return 0;
  const int count_neg = accumulate(cbegin(vec), cend(vec), 0,
                                   [](int x, int y) { return x + (y < 0); });
  const int max_neg = accumulate(cbegin(vec), cend(vec), lmt<int>::min(),
      [](int x, int y){
      return y >= 0 ? x : max(x, y);
      });
  const auto prod = accumulate(cbegin(vec), cend(vec), 1, multiplies<int>{});
  if(count_neg % 2 == 1){
    if(count_neg == 1 and count_zero == size - 1) return 0;;
    return prod / max_neg;
  }
  return prod;
}
