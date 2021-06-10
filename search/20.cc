#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <set>
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

int main(int argc, const char **argv) {
  using lint = long long int;
  int t;
  cin >> t;
  while (t--) {
    int n, q;
    cin >> n >> q;
    /* auto is_mergeable = [](const pair<int, int> &p1, const pair<int, int> &p2) { */
    /*   return p1.second >= p2.first || p1.first == p2.first; */
    /* }; */
    vector<pair<lint, lint>> intervals(n);
    for (int i = 0; i < n; i++) {
      cin >> intervals[i].first >> intervals[i].second;
    }
    sort(intervals.begin(), intervals.end());
    int index = 0;
    for (int i = 1; i < n; i++) {
      if (intervals[index].second >= intervals[i].first) {
        intervals[index].second =
            max(intervals[index].second, intervals[i].second);
      } else {
        index++;
        intervals[index] = intervals[i];
      }
    }
    while (q--) {
      int k;
      cin >> k;
      int ans = -1;
      for (int i = 0; i <= index; i++) {
        const auto& pr = intervals[i];
        if (k <= pr.second - pr.first + 1) {
          ans = pr.first + k - 1;
          break;
        } else {
          k -= (pr.second - pr.first + 1);
        }
      }
      cout << ans << "\n";
    }
  }
  return 0;
}
