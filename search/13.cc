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

void mergeInefficient(int arr1[], int arr2[], int n, int m) {
  auto rearrange = [&]{
    for(int i = 1; i < m; i++){
      if(arr2[i] < arr2[i - 1]){
        swap(arr2[i], arr2[i - 1]);
      }
    }
  };
  for(int i = 0; i < n; i++){
    if(arr1[i] > arr2[0]){
      swap(arr1[i], arr2[0]);
      rearrange();
    }
  }
}

void merge(int arr1[], int arr2[], int n, int m) {
  auto at = [&](int i) -> int&{
    if(i >= 0 && i < n){
      return arr1[i];
    }else if(i >= n && i < m + n){
      return arr2[i - n];
    }
  };
  int gap = (m + n) % 2 ? (m + n) / 2 + 1 : (m + n) / 2;
  while(gap > 0){
    int i = 0;
    int j = gap;
    while(j < (m + n)){
      if(at(i) > at(j)){
        swap(at(i), at(j));
      }
      i++;
      j++;
    }
    gap = ((gap % 2 == 0) || gap == 1) ? gap / 2 : gap / 2 + 1;
  }
}

int main(int argc, const char** argv) {
  int arr1[] = {1, 3, 5, 7};
  int arr2[] = {0, 2, 6, 8, 9};
  int n = sizeof(arr1) / sizeof(int);
  int m = sizeof(arr2) / sizeof(int);
  merge(arr1, arr2, n, m);
  return 0;
}
