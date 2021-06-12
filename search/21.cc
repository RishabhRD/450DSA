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

int peak_ele(const vector<int>& arr){
  const int size = arr.size();
  if(size == 0){
    return -1;
  }
  int low = 0;
  int high = size - 1;

  int ans = -1;
  while(low <= high){
    if(low == high){
      return low;
    }
    int mid = (low + high) / 2;
    if(mid == 0){
      if(arr[mid] >= arr[mid + 1]){
        return mid;
      }
    }else if(mid == size - 1){
      if(arr[mid] >= arr[mid - 1]){
        return mid;
      }
    }else{
      if(arr[mid] >= arr[mid - 1] && arr[mid] >= arr[mid + 1]){
        return mid;
      }else if(arr[mid] > arr[high]){
        high = mid + 1;
      }else if(arr[mid] < arr[high]){
        low = mid - 1;
      }
    }
  }
  return -1;
}
