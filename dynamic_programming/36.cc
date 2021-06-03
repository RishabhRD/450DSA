#include <algorithm>
#include <array>
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
template <typename T> constexpr auto accessor(T &t) {
  return [&](int i) -> typename T::value_type & { return t.at(i); };
}

template <typename T> constexpr auto accessor(const T &t) {
  return [&](int i) { return t.at(i); };
}

template <typename T> constexpr auto const_accessor(T &t) {
  return [&](int i) { return t.at(i); };
}

template <typename T> constexpr auto matrix_accessor(T &t) {
  return [&](int i, int j) ->
         typename T::value_type::value_type & { return t.at(i).at(j); };
}

template <typename T> constexpr auto matrix_accessor(const T &t) {
  return [&](int i, int j) { return t.at(i).at(j); };
}

template <typename T> constexpr auto const_matrix_accessor(T &t) {
  return [&](int i, int j) { return t.at(i).at(j); };
}

template <typename T> using lmt = std::numeric_limits<T>;

template <typename U, typename V>
int knapsack(const U& weight, const V& value, const int w, const int size){
  vector<int> dp(w + 1);
  auto sol = accessor(dp);
  for(int i = 0; i < size; i++){
    for(int j = 0; j < w + 1; j++){
      if(weight(i) <= j){
        sol(j) = max(sol(j), sol(j - weight(i)) + value(i));
      }
    }
  }
  return sol(w);
}

int knapSack(int N, int W, int val[], int wt[]) {
  vector<int> weights;
  vector<int> values;


  std::copy(wt, wt + N, std::back_inserter(weights));
  std::copy(val, val + N, std::back_inserter(values));

  auto weight = const_accessor(weights);
  auto value = const_accessor(values);

  return knapsack(weight, value, W, N);
}

int main(int argc, const char** argv) {
  int val[] = {1, 4, 5, 7};
  int wt[] = {1, 3, 4, 5};
  int n = 4, w = 8;
  cout << knapSack(n, w, val, wt) << endl;
    return 0;
}
