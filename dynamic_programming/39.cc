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

int ep(const vector<int>& vec){
  const int size = vec.size();
  auto at = accessor(vec);
  int sum = std::accumulate(vec.begin(), vec.end(), 0);
  if(sum % 2){
    return false;
  }

  sum = sum/2;

  vector<bool> dp(sum + 1);
  auto sol = accessor(dp);

  for(int i = 0; i <= sum; i++){
    sol(i) = 0;
  }

  sol(0) = true;

  for(int i = 0; i < size; i++){
    for(int j = sum; j >= 0; j--){
      if(j - at(i) >= 0)
        sol(j) = sol(j) || sol(j - at(i));
    }
  }
  cout << dp << endl;
  return sol(sum) > 0;
}

int equalPartition(int N, int arr[]) {
  vector<int> vec;
  std::copy(arr, arr + N, std::back_inserter(vec));
  return ep(vec);
}


int main(int argc, const char** argv) {
  std::cout << ep({1, 3, 5}) << std::endl;
    return 0;
}
