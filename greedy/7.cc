#include <algorithm>
#include <set>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>

using namespace std;

template <typename T>
concept is_container = requires(T a) {
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

template <typename T, std::size_t N>
constexpr std::size_t array_size(const T (&)[N]) noexcept {
  return N;
}

ostream& operator<<(ostream& os, const pair<int, int>& pr){
  os << "(" << pr.first << ", " << pr.second << ")";
  return os;
}

int findPlatform(int arr[], int dep[], int n) {
  sort(arr, arr + n);
  sort(dep, dep + n);
  int i = 0, j = 0;
  int cur_platforms = 0;
  int max_platforms = 0;
  while(i < n and j < n){
    if(arr[i] <= dep[j]){
      cur_platforms++;
      max_platforms = max(max_platforms, cur_platforms);
      i++;
    }else{
      cur_platforms--;
      j++;
    }
  }
  return max_platforms;
}

int main(int argc, const char** argv) {
  int start[] = {900, 940, 950, 1100, 1500, 1800};
  int end[] = {910, 1200, 1120, 1130, 1900, 2000};
  cout << findPlatform(start, end, array_size(start)) << endl;
    return 0;
}
