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

int maxProfit(const vector<int> &vec, int k) {
  const auto at = accessor(vec);
  const auto size = vec.size();

  vector<vector<int>> dp(k + 1, vector<int>(size));
  const auto sol = matrix_accessor(dp);

  for (int i = 1; i <= k; i++) {
    for (int j = 1; j < size; j++) {
      sol(i, j) = sol(i, j - 1);
      for (int m = 0; m < j; m++) {
        sol(i, j) = max(sol(i, j), at(j) - at(m) + sol(i - 1, m));
      }
    }
  }

  return sol(k, size - 1);
}

// This doesn't involve m in algorithm. Why?
// Because we can store in a variable what was maximum profit we could get
// in a variable
int maxProfitOptmized(const vector<int> &vec, int k) {
  const auto at = accessor(vec);
  const auto size = vec.size();

  vector<vector<int>> dp(k + 1, vector<int>(size));
  const auto sol = matrix_accessor(dp);

  for (int i = 1; i <= k; i++) {
    int variable_profit = lmt<int>::min();
    for (int j = 1; j < size; j++) {
      variable_profit =  max(variable_profit, sol(i - 1, j - 1) - at(j - 1));
      sol(i, j) = max(sol(i, j - 1), at(j) + variable_profit);
    }
  }

  return sol(k, size - 1);
}


int maxProfit(int K, int N, int A[]) {
  vector<int> vec;
  std::copy(A, A + N, std::back_inserter(vec));
  return maxProfitOptmized(vec, K);
}

int main(int argc, const char **argv) {
  cout << maxProfit({10, 22, 5, 75, 65, 80}, 2) << endl;
  return 0;
}
