#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <stack>
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

long long getMaxArea(long long arr[], int n) {
  auto fill_bar_dist = [&](stack<long long> &st, vector<long long> &range,
                           int i, const int default_value, const int incr) {
    while (not st.empty()) {
      int top = st.top();
      if (arr[top] >= arr[i]) {
        st.pop();
      } else {
        break;
      }
    }
    if (!st.empty()) {
      range[i] = st.top() + incr;
    } else {
      range[i] = default_value;
    }
    st.push(i);
  };
  vector<long long> left_range(n);
  stack<long long> left_stack;
  for (int i = 0; i < n; i++) {
    fill_bar_dist(left_stack, left_range, i, 0, 1);
  }
  vector<long long> right_range(n);
  stack<long long> right_stack;
  for (int i = n - 1; i >= 0; i--) {
    fill_bar_dist(right_stack, right_range, i, n - 1, -1);
  }
  /* cout << left_range << endl; */
  /* cout << right_range << endl; */
  long long max_area = 0;
  for (int i = 0; i < n; i++) {
    long long current_area = arr[i] * (right_range[i] - left_range[i] + 1);
    max_area = max(max_area, current_area);
  }
  return max_area;
}

int main(int argc, const char **argv) {
  long long arr[] = {1, 2, 3, 4, 5};
  cout << getMaxArea(arr, size(arr)) << endl;
  return 0;
}
