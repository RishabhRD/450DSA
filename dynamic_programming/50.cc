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

vector<vector<bool>> createPalindromeMatrix(const string& str){
  const auto size = str.size();
  vector<vector<bool>> dp(size, vector<bool>(size));
  const auto at = accessor(str);
  const auto sol = matrix_accessor(dp);

  for(int i = 0; i < size; i++){
    sol(i, i) = true;
  }

  for(int length = 2; length <= size; length++){
    for(int i = 0; i < size - length + 1; i++){
      auto j = i + length - 1;
      if(at(i) == at(j)){
        if(j - i == 1){
          sol(i, j) = true;
        }else{
          sol(i, j) = sol(i + 1, j - 1);
        }
      }
    }
  }
  return dp;
}

int palindromicPartition(const string& str){
  const auto size = str.size();
  vector<int> dp(size, lmt<int>::max());
  const auto at = accessor(str);
  const auto sol = accessor(dp);
  vector<vector<bool>> palin_results = createPalindromeMatrix(str);
  auto is_palin = matrix_accessor(palin_results);
  if(is_palin(0, size - 1)){
    return 0;
  }

  sol(0) = 0;

  for(int i = 0; i < size; i++){
    if(is_palin(0, i)){
      sol(i) = 0;
    }
    if(sol(i) >= 0){
      for(int j = i + 1; j < size; j++){
        if(is_palin(i+1, j)){
          sol(j) = min(sol(i) + 1, sol(j));
        }
      }
    }
    /* cout << dp << endl; */
  }


  return sol(size - 1);
}

int main(int argc, const char** argv) {
  cout << palindromicPartition("aaabba") << endl;
    return 0;
}
