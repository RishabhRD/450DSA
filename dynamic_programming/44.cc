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

template <typename T>
using lmt = std::numeric_limits<T>;

struct job{
  int start;
  int end;
  int value;
};

bool operator<(const job& j1, const job& j2){
  return j1.end <= j2.start;
}

std::ostream& operator<<(std::ostream& os, const job& j){
  os << '{';
  os << j.start << ", " << j.end << ", "<< j.value;
  os << '}';
  return os;
}

int schedule(vector<job>& vec){
  std::sort(vec.begin(), vec.end(), [](const job& j1, const job& j2){
      return j1.end < j2.end;
      });
  const auto at = const_accessor(vec);
  const auto value = [&](int i){
    return vec.at(i).value;
  };
  const auto searchLess = [&](const int i, const job& j){
    auto end = std::begin(vec);
    std::advance(end, i);
    auto res = std::lower_bound(std::begin(vec), end, j);
    return (res - std::begin(vec)) - 1;
  };
  const auto size = vec.size();
  vector<int> dp(size);
  auto sol = accessor(dp);

  sol(0) = value(0);
  int ans = value(0);
  for(int i = 1; i < size; i++){
    sol(i) = max(value(i), sol(i - 1));
    auto j = searchLess(i, at(i));
    if(j != -1){
      sol(i) = max(sol(i), value(i) + sol(j));
    }
    ans = max(sol(i), ans);
  }

  return ans;
}

int main(int argc, const char** argv) {
  vector<job> jobs = {
    {3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}
  };
  cout << schedule(jobs) << endl;
    return 0;
}
