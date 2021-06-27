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

int maxMeetings(const int start[], const int end[], int n) {
  if(n == 0) return 0;
  vector<pair<int, int>> timings;
  for(int i = 0; i < n; i++){
    timings.emplace_back(start[i], end[i]);
  }
  sort(timings.begin(), timings.end(), [](const auto& a , const auto& b){
      return a.second < b.second;
      });

  auto can_happen = [](const auto& prev, const auto& cur){
    return cur.first > prev.second;
  };

  int count = 1;
  auto& prev = timings[0];
  for(int i = 1; i < n; i++){
    if(can_happen(prev, timings[i])){
      count++;
      prev = timings[i];
    }
  }
  return count;
}

int main(int argc, const char** argv) {
  const int start[] = {1,3,0,5,8,5};
  const int end[] = {2,4,6,7,9,9};
  const int size = sizeof(start) / sizeof(int);
  cout << maxMeetings(start, end, size) << endl;
    return 0;
}
