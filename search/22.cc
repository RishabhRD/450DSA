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


int kthElementIneff(int arr1[], int arr2[], int n, int m, int k) {
  int i = 0;
  int j = 0;
  int count = 1;
  int curEle;
  while(i < n && j < m){
    if(arr1[i] < arr2[j]){
      curEle = arr1[i];
      i++;
    }else{
      curEle = arr2[j];
      j++;
    }
    if(count == k){
      return curEle;
    }
    count++;
  }
  if(i >= n){
    while(j < m){
      curEle = arr2[j];
      j++;
      if(count == k){
        return curEle;
      }
      count++;
    }
  }
  if(j >= m){
    while(i < n){
      curEle = arr1[i];
      i++;
      if(count == k){
        return curEle;
      }
      count++;
    }
  }
  return -1;
}

template <typename T>
using lmt = std::numeric_limits<T>;
int kthElement(int arr1[], int arr2[], int n, int m, int k) {
  if(k > m + n || k <= 0){
    return -1;
  }
  if(n > m){
    return kthElement(arr2, arr1, m, n, k);
  }
  if(n == 0){
    return arr2[k - 1];
  }
  int low = max(0, k - m);
  int high = min(n, k);
  int ans = -1;
  while(low <= high){
    int mid1 = (low + high) / 2;
    int mid2 = k - mid1;
    int l1 = mid1 == 0 ? lmt<int>::min() : arr1[mid1 - 1];
    int l2 = mid2 == 0 ? lmt<int>::min() : arr2[mid2 - 1];
    int r1 = mid1 == n ? lmt<int>::max() : arr1[mid1];
    int r2 = mid2 == m ? lmt<int>::max() : arr2[mid2];
    if(l1 > r2){
      high = mid1 - 1;
    }else if(l2 > r1){
      low = mid1 + 1;
    }else{
      ans = max(l1, l2);
      break;
    }
  }
  return ans;
}

int main(int argc, const char** argv) {
  int arr1[] = {24, 50, 92, 95};
  int arr2[] = {1, 2, 6, 6, 8, 8, 11, 11, 12, 12, 13, 13, 14, 15, 16, 16, 17, 17, 17, 19, 21, 21, 22, 22, 24, 24, 25, 27, 29, 32, 33, 34, 35, 35, 35, 36, 38, 40, 41, 43, 44, 45, 46, 46, 47, 48, 50, 50, 50, 54, 54, 54, 54, 54, 57, 58, 60, 60, 61, 62, 67, 68, 69, 73, 73, 74, 75, 76, 78, 78, 79, 80, 81, 82, 82, 83, 83, 85, 86, 87, 87, 88, 88, 90, 91, 91, 92, 92, 92, 93, 95, 95, 95, 96, 97, 97, 98};
  int n = sizeof(arr1)/sizeof(int);
  int m = sizeof(arr2)/sizeof(int);
  cout << kthElement(arr1, arr2, n, m, 98) << endl;
    return 0;
}
