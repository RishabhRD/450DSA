#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <queue>
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

string solve(int arr[], int n) {
  vector<int> vec(arr, arr + n);
  if (n % 2) {
    vec.push_back(0);
  }
  sort(begin(vec), end(vec), greater<int>{});
  int carry = 0;
  string str;
  for (int i = 0; i < n; i = i + 2) {
    int sum = vec[i] + vec[i + 1] + carry;
    carry = sum / 10;
    sum = sum % 10;
    str += (char)(sum + '0');
  }
  if (carry != 0) {
    str += (char)(carry + '0');
  }
  reverse(begin(str), end(str));
  auto itr = find_if(cbegin(str), cend(str), [](char c) { return c != '0'; });
  if(cbegin(str) != itr){
    str.erase(cbegin(str), itr);
  }
  return str;
}

int main(int argc, const char **argv) {
  int arr[]{5, 3, 0, 7, 4};
  cout << solve(arr, size(arr)) << endl;
  return 0;
}
