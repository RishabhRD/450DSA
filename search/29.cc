
#include <algorithm>
#include <array>
#include <cmath>
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

int findPages(int arr[], int n, int m) {
  if(m > n){
    return -1;
  }

  int low = *min_element(arr, arr + n);
  int high = accumulate(arr, arr + n, 0);

  auto allocatable = [&](int barrier) -> bool{
    int pages_allocated = 0;
    int students_used = 1;
    int i = 0;
    while(i < n){
      if(barrier < arr[i]){
        return false;
      }
      if(pages_allocated + arr[i] <= barrier){
        pages_allocated += arr[i];
        i++;
      }else{
        /* cout << pages_allocated << " " << pages_allocated + arr[i] << " " << barrier << " " << students_used << endl; */
        pages_allocated = 0;
        students_used++;
        if(students_used > m){
          return false;
        }
      }
    }
    return true;
  };

  int ans = -1;
  while(low <= high){
    int mid = (low + high) / 2;
    if(allocatable(mid)){
      high = mid - 1;
      ans = mid;
    }else{
      low = mid + 1;
    }
  }
  return ans;
}

int main(int argc, const char **argv) {
  int arr[] = {12, 34, 67, 90};
  int n = sizeof(arr) / sizeof(int);
  int m = 2;
  cout << findPages(arr, n, m) << endl;
  return 0;
}
