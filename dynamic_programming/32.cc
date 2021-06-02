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

template <typename T>
long double count(long long int n, long long int current, const T& at) {
  if(n == 0){
    return 0;
  }else if(n < 0){
    return -1;
  }

  if(at(n, current) != -1){
    return at(n, current);
  }

  auto c3 = count( n - 3, current + 3, at);
  auto c5 = count( n - 5, current + 5, at);
  auto c10 = count( n - 10, current + 10, at);

  long double ans = 0;
  if(c3 >= 0){
    if(current == n - 3){
      ans += 1 + c3;
    }else{
      ans += 0.5 + c3;
    }
  }
  if(c5 >= 0){
    if(current == n - 5){
      ans += 1 + c5;
    }else{
      ans += 0.5 + c5;
    }
  }
  if(c5 >= 0){
    if(current == n - 10){
      ans += 1 + c10;
    }else{
      ans += 0.5 + c10;
    }
  }
  at(n, current) = ans;
  return ans;
}

long long count(int n) {
  vector<int> vec(n + 1);
  auto at = accessor(vec);
  at(0) = 1;

  for(int i = 3; i <= n; i++){
    at(i) += at(i - 3);
  }
  for(int i = 5; i <= n; i++){
    at(i) += at(i - 5);
  }
  for(int i = 10; i <= n; i++){
    at(i) += at(i - 10);
  }
  return at(n);
}

int main(int argc, const char** argv) {
  cout<< (long long)count(30) << endl;
    return 0;
}
