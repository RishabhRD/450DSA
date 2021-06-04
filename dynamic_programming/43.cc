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

// It was a DP approach like LIS. But we can do even better than DP.
int AlternatingaMaxLengthDP(const vector<int>&nums){
  const auto at = accessor(nums);
  const auto size = nums.size();
  if(size == 0){
    return 0;
  }else if(size == 1){
    return 1;
  }

  auto dp = create_array<2>(vector<int>(size, 1));
  const auto sol = matrix_accessor(dp);

  auto res = 1;

  for(int i = 1; i < size; i++){
    for(int j = 0; j < i; j++){
      if(at(i) > at(j)){
        sol(0, i) = max(sol(0, i), 1 + sol(1, j));
      }else if(at(i) < at(j)){
        sol(1, i) = max(sol(1, i), 1 + sol(0, j));
      }
    }
    res = max({res, sol(0, i), sol(1, i)});
  }

  return res;
}


// If we observe counting the number of peaks(both +ve and -ve) is answer
int AlternatingaMaxLength(const vector<int>&nums){
  const auto at = accessor(nums);
  const auto size = nums.size();
  if(size == 0){
    return 0;
  }else if(size == 1){
    return 1;
  }
  // logic of counting peaks here is positive peak would be always 1 more than
  // negative peak or negative peak would be always 1 more than positive peak.
  // So, if we encounter a postive peak make number of positive peak 1
  // more than number of negative peaks till now and vice versa.
  int inc = 1;
  int dec = 1;
  for(int i = 1; i < size; i++){
    if(at(i) > at(i - 1)){
      inc = dec + 1;
    }else if(at(i) < at(i - 1)){
      dec = inc + 1;
    }

  }
  return max(inc, dec);
}

int main(int argc, const char** argv) {
  cout << AlternatingaMaxLength({1, 6, 15}) << endl;
    return 0;
}
