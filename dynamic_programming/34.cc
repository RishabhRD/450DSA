#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>

using namespace std;

template <typename T> concept is_container = requires(T a) {
  a.begin();
  a.end();
};

std::ostream &operator<<(std::ostream &os, const is_container auto &cont) {
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
  return [&](int i) -> typename T::value_type & { return t.at(i); };
}

template <typename T> constexpr auto accessor(const T &t) {
  return [&](int i) { return t.at(i); };
}

template <typename T> constexpr auto const_accessor(T &t) {
  return [&](int i) { return t.at(i); };
}

template <typename T> constexpr auto matrix_accessor(T &t) {
  return [&](int i, int j) ->
         typename T::value_type::value_type & { return t.at(i).at(j); };
}

template <typename T> constexpr auto matrix_accessor(const T &t) {
  return [&](int i, int j) { return t.at(i).at(j); };
}

template <typename T> constexpr auto const_matrix_accessor(T &t) {
  return [&](int i, int j) { return t.at(i).at(j); };
}

template <typename T> using lmt = std::numeric_limits<T>;

// dp here was longest sum suffix
int mss(const vector<int> &vec) {
  auto at = accessor(vec);
  const auto size = vec.size();
  vector<int> dp(size);
  auto sol = accessor(dp);
  sol(0) = at(0);

  for (int i = 1; i < size; i++) {
    sol(i) = max(at(i), sol(i - 1) + at(i));
  }
  return *max_element(dp.begin(), dp.end());
}

// converting this dp to kadane logically
int kadane(const vector<int> &vec) {
  auto at = accessor(vec);
  const auto size = vec.size();
  auto max_till_now = at(0);
  auto largest_suffix_till_now = at(0);

  for (int i = 1; i < size; i++) {
    largest_suffix_till_now = max(at(i), largest_suffix_till_now + at(i));
    max_till_now = max(max_till_now, largest_suffix_till_now);
  }
  return max_till_now;
}

int maxSubarraySum(int arr[], int n) {
  vector<int> vec;
  std::copy(arr, arr + n, std::back_inserter(vec));
  return mss(vec);
}
