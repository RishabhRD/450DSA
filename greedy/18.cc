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

template<typename T>
T absolute(T ele){
  return ele >= 0 ? ele : -ele;
}

long long int maxSum(int arr[], int n) {
  sort(arr, arr + n);
  vector<long long> final_seq;
  int i = 0, j = n - 1;
  while (i <= j) {
    if (i == j) {
      final_seq.push_back(arr[i]);
    } else {
      final_seq.push_back(arr[i]);
      final_seq.push_back(arr[j]);
    }
    i++;
    j--;
  }
  return inner_product(cbegin(final_seq), prev(cend(final_seq)),
                       next(cbegin(final_seq)), 0, plus<long long>{},
                       [](auto a, auto b) { return abs(a - b); }) +
         abs(final_seq.front() - final_seq.back());
}

int main(int argc, const char** argv) {
  int arr[] = {1, 4, 2, 8};
  constexpr int n = array_size(arr);
  cout << maxSum(arr, n) << endl;
    return 0;
}
