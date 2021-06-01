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


int minimumCost(int Cost[], int N, int w) {
  vector<int> costs;
  vector<int> weights;
  for (int i = 0; i < N; i++) {
    if (Cost[i] != -1) {
      costs.push_back(Cost[i]);
      weights.push_back(i + 1);
    }
  }
  const auto size = costs.size();
  auto cost = const_accessor(costs);
  auto weight = const_accessor(weights);

  vector<vector<int>> min_costs(w + 1, vector<int>(size + 1));
  auto min_cost = matrix_accessor(min_costs);
  for (int i = 0; i < w + 1; i++) {
    min_cost(i, 0) = lmt<int>::max();
  }

  for (int i = 0; i < size + 1; i++) {
    min_cost(0, i) = 0;
  }

  for (int i = 1; i < w + 1; i++) {
    for (int j = 1; j < size + 1; j++) {
      if (weight(j - 1) > i) {
        min_cost(i, j) = min_cost(i, j - 1);
      } else {
        auto other_cost = min_cost(i - weight(j - 1), j);
        if (other_cost == lmt<int>::max()) {
          min_cost(i, j) = min_cost(i, j - 1);
        } else {
          min_cost(i, j) = min(min_cost(i, j - 1),
                               min_cost(i - weight(j - 1), j) + cost(j - 1));
        }
      }
    }
  }

  if (min_cost(w, size) == lmt<int>::max()) {
    min_cost(w, size) = -1;
  }
  return min_cost(w, size);
}

