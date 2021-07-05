#include <queue>
#include <algorithm>
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

long long int maximizeSum_nlogn(long long int a[], int n, int k) {
  sort(a, a + n);
  int i = 0;
  while(k--){
    if(a[i] == 0){
      break;
    }
    a[i] = -a[i];
    if(i != n - 1){
      if(a[i + 1] < a[i]){
        i++;
      }
    }
  }
  return accumulate(a, a + n, 0);
}

long long int maximizeSum(long long int a[], int n, int k) {
  priority_queue<int, vector<int>, greater<int>> pq;
  for(int i = 0; i < n; i++){
    pq.push(a[i]);
  }
  while(k--){
    int tmp = pq.top();
    pq.pop();
    pq.push(-tmp);
  }
  int sum = 0;
  while(!pq.empty()){
    sum += pq.top();
    pq.pop();
  }
  return sum;
}

int main(int argc, const char** argv) {
  long long arr[] = {-1, -2, -3, -4, -5};
  constexpr int n = array_size(arr);
  cout << maximizeSum(arr, n, 10) << endl;
    return 0;
}
