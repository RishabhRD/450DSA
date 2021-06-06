#include <iostream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>
#include <array>

using namespace std;

template <typename T> concept is_container = requires(T a) {
  a.begin();
  a.end();
};

template <is_container T>requires (!std::same_as<T, std::string>)
std::ostream &operator<<(std::ostream &os, const T &cont) {
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
template <typename T>
constexpr auto accessor(T& t){
  return [&](int i) -> typename T::reference{
    return t.at(i);
  };
}

template <typename T>
constexpr auto accessor(const T& t){
  return [&](int i){
    return t.at(i);
  };
}

template <typename T>
constexpr auto const_accessor(T& t){
  return [&](int i){
    return t.at(i);
  };
}

template <typename T>
constexpr auto matrix_accessor(T& t){
  return [&](int i, int j) -> typename T::value_type::reference{
    return t.at(i).at(j);
  };
}

template <typename T>
constexpr auto matrix_accessor(const T& t){
  return [&](int i, int j) {
    return t.at(i).at(j);
  };
}

template <typename T>
constexpr auto const_matrix_accessor(T& t){
  return [&](int i, int j) {
    return t.at(i).at(j);
  };
}

template <typename T>
using lmt = std::numeric_limits<T>;

long long getCount(int n){
  vector<vector<int>> keypad = {
    {0, 8},
    {1, 2, 4},
    {2, 1, 3, 5},
    {3, 2, 6},
    {4, 1, 5, 7},
    {5, 2, 4, 6, 8},
    {6, 3, 5, 9},
    {7, 4, 8},
    {8, 7, 5, 9, 0},
    {9, 6, 8}
  };

  const auto at = accessor(keypad);

  auto dp = create_array<10>(vector<long long int>(n + 1));
  auto sol = matrix_accessor(dp);
  for(int i = 0 ; i < 10; i++){
    sol(i, 1) = 1;
  }


  for(int i = 2; i <= n; i++){
    for(int j = 0; j < 10; j++){
      auto& vec = at(j);
      long long int total_sol = 0;
      for(auto x : vec){
        total_sol += sol(x, i - 1);
      }
      sol(j, i) = total_sol;
    }
  }


  long long int ans = 0;
  for(int i = 0; i < 10; i++){
    ans += sol(i, n);
  }
  return ans;
}

int main(int argc, const char** argv) {
  cout << getCount(2) << endl;
    return 0;
}
