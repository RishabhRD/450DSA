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
template <typename T>
constexpr auto accessor(T& t){
  return [&](int i) -> typename T::value_type&{
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
  return [&](int i, int j) -> typename T::value_type::value_type&{
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

int longestCommonSubstr (const string& S1, const string& S2, int n, int m) {
  const auto size1 = S1.size();
  const auto size2 = S2.size();
  auto at1 = accessor(S1);
  auto at2 = accessor(S2);

  vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1));
  auto sol = matrix_accessor(dp);

  int result = 0;
  for(int i = 1; i <= size1; i++){
    for(int j = 1; j <= size2; j++){
      if(at1(i - 1) == at2(j - 1)){
        sol(i,j) = 1 + sol(i - 1, j - 1);
        result = max(result, sol(i, j));
      }else{
        sol(i, j) = 0;
      }
    }
  }


  return result;
}

int main(int argc, const char** argv) {
  string s1 = "abc";
  string s2 = "acb";
  cout << longestCommonSubstr(s1, s2, s1.size(), s2.size()) << endl;
    return 0;
}
