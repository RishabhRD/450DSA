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

long long int countPS(string str) {
  constexpr int mod = 1000000007;
  const auto at = const_accessor(str);
  const auto size = str.size();

  vector<vector<int>> dp(size, vector<int>(size));
  auto sol = matrix_accessor(dp);

  for(int i = 0; i < size; i++){
    sol(i, i) = 1;
  }

  for(int length = 2; length <= size; length++){
    for(int i = 0; i < size - length + 1; i++){
      auto j = i + length - 1;
      if(at(i) == at(j)){
        sol(i, j) = (1 + ((sol(i + 1, j) + sol(i, j - 1)) % mod + mod) % mod) % mod;
      }else{
        sol(i, j) = (((sol(i + 1, j) + sol(i , j - 1)) % mod + mod) % mod - sol(i + 1, j - 1)) % mod; 
      }
    }
  }

  printMatrix(dp);

  return sol(0, size - 1);
}

int main(int argc, const char** argv) {
  cout << countPS("aaaa") << endl;
    return 0;
}
