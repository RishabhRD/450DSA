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

template <typename T, typename U>
long long ma(const T& at, const U& sol, int i, int j){
  if(i > j){
    return 0;
  }
  if(i == j){
    sol(i, j) =  at(i);
  }else if(j - i == 1){
    sol(i, j) =  max(at(i), at(j));
  }else{
    sol(i, j) = max({
        at(i) + min({
            ma(at, sol, i + 2, j),
            ma(at, sol, i + 1, j - 1)
            }),
        at(j) + min({
            ma(at, sol, i, j - 2),
            ma(at, sol, i + 1, j - 1)
            })
        });
  }
  return sol(i, j);
}

long long ma(const vector<int>& vec){
  const int size = vec.size();
  vector<vector<int>> dp(size, vector<int>(size));
  auto sol = matrix_accessor(dp);
  auto at = accessor(vec);

  for(int i = 0; i < size; i++){
    sol(i, i) = i;
  }

  for(int i = 0; i < size - 1; i++){
    sol(i, i + 1) = max(at(i), at(i + 1));
  }

  for(int length = 3; length <= size; length++){
    for(int i = 0; i < size - length + 1; i++){
      const int j = i + length - 1;
      sol(i, j) = max(
          at(i) + min(sol(i + 2, j), sol(i + 1, j - 1)),
          at(j) + min(sol(i, j - 2), sol(i + 1, j - 1))
      );
    }
  }

  return sol(0, size - 1);
}

long long maximumAmount(int arr[], int n) {
  vector<int> vec;
  std::copy(arr, arr + n, std::back_inserter(vec));
  return ma(vec);
}

int main(int argc, const char** argv) {
  cout << ma({5, 3, 7, 10}) << endl;;
    return 0;
}
