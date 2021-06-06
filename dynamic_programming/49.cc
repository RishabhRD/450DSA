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

/* template <typename T> */
/* constexpr auto accessor(const T& t){ */
/*   return [&](auto... x){ */
/*     return t.at(x)...; */
/*   }; */
/* } */

template <typename T>
using lmt = std::numeric_limits<T>;

int numBst(const vector<int>& freq){
  auto at = accessor(freq);
  const int size = freq.size();
  vector<vector<int>> dp(size, vector<int>(size, 0));
  auto sol = matrix_accessor(dp);
  auto csol = [&](int i, int j){
    if((i < 0) || (j < 0)){
      return 0;
    }
    if(j >= size || i >= size){
      return 0;
    }
    return dp.at(i).at(j);
  };

  vector<int> frequencies(size);
  frequencies.at(0) = at(0);
  for(int i = 1; i < size; i++){
    frequencies.at(i) = at(i) + frequencies.at(i - 1);
  }

  auto freqSum = [&](int i, int j){
    if(i == 0){
      return frequencies.at(j);
    }else{
      return frequencies.at(j) - frequencies.at(i - 1);
    }
  };

  
  for(int i = 0; i < size; i++){
    sol(i, i) = at(i);
  }

  for(int length = 2; length <= size; length++){
    for(int i = 0; i < size - length + 1; i++){
      auto j = i + length - 1;
      sol(i, j) = lmt<int>::max();
      for(int k = i; k <= j; k++){
        int c = csol(i, k - 1) + csol(k + 1, j) + freqSum(i, j);
        sol(i, j) = min(sol(i, j), c);
      }
    }
  }
  return csol(0, size - 1);
}

int main(int argc, const char** argv) {
  cout << numBst({34, 8, 50}) << endl;
    return 0;
}
