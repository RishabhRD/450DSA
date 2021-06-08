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


bool binary_search(int* arr, int low, int high, int ele){
  while(low <= high){
    int mid = (low + high) / 2;
    if(arr[mid] == ele){
      return true;
    }else if(arr[mid] < ele){
      low = mid + 1;
    }else{
      high = mid - 1;
    }
  }
  return false;
}

bool findPair(int arr[], int size, int n){
  sort(arr, arr + size);
  int low = 0;
  int high = 1;
  while(low < size && high < size){
    int diff = abs(arr[high] - arr[low]);
    if(low != high && diff == n){
      return true;
    }else if(diff > n){
      low++;
    }else{
      high++;
    }
  }
  return false;
}

int main(int argc, const char** argv) {
  int arr[] = {5, 20, 3, 2, 5, 80};
  cout << findPair(arr, sizeof(arr)/sizeof(int), 78) << endl;
    return 0;
}
