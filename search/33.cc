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

long long intersection(long long* arr, long long low, long long mid, long long high){
  int n1 = mid - low + 1;
  int n2 = high - mid;
  long long firstArray[n1];
  long long secondArray[n2];
  auto begin = arr + low;
  std::copy(begin, begin + n1, firstArray);
  begin=  arr + mid + 1;
  std::copy( begin, begin + n2, secondArray);
  long long index = low;
  long long i = 0;
  long long j = 0;
  long long ans = 0;
  while(i < n1 && j < n2){
    if(firstArray[i] <= secondArray[j]){
      arr[index] = firstArray[i];
      i++;
    }else{
      ans += n1 - i;
      arr[index] = secondArray[j];
      j++;
    }
    index++;
  }
  if(i < n1){
    std::copy(firstArray + i, firstArray + n1, arr + index);
  }else{
    std::copy(secondArray + j, secondArray + n2, arr + index);
  }
  return ans;
}


long long icount(long long* arr, long long low, long long high){
  if(low >= high){
    return 0;
  }
  long long mid = low + (high - low) / 2;
  long long ans = 0;
  ans += icount(arr, low, mid);
  ans += icount(arr, mid + 1, high);
  ans += intersection(arr, low, mid, high);
  return ans;
}


long long int inversionCount(long long arr[], long long N) {
  return icount(arr, 0, N - 1);
}

int main(int argc, const char** argv) {
  long long arr[] = {2, 4, 1, 3, 5};
  int n = sizeof(arr) / sizeof(long long);
  cout << inversionCount(arr, n) << endl;
  /* for(auto x : arr){ */
  /*   cout << x << " "; */
  /* } */
    return 0;
}
