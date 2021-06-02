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
template <typename T>
constexpr auto accessor(T& t){
  return [&](int i) -> typename T::value_type&{
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
  return [&](int i, int j) -> typename T::value_type::value_type&{
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

template <typename T>
int removals(const vector<int>& numbers,  int i, int j, T& dp, int k){
  if(i >= j){
    return 0;
  }
  if(numbers.at(j) - numbers.at(i) <= k){
    return 0;
  }
  if(dp(i, j) != -1){
    return dp(i, j);
  }

  // TODO: make it a bottom up approach
  dp(i, j) = 1 + min(removals(numbers, i + 1, j, dp, k), removals(numbers, i, j - 1, dp, k));
  return dp(i, j);
}

int removals(const vector<int>& numbers, int k){
  const int size = numbers.size();
  vector<vector<int>> dp(size, vector<int>(size, -1));
  auto sol = matrix_accessor(dp);
  return removals(numbers, 0, size - 1, sol, k);
}

int removals_nlogn(vector<int>& numbers, int k){
  sort(numbers.begin(), numbers.end());

  auto at = accessor(numbers);

  auto itr = [&](int i){
    auto iter = numbers.begin();
    std::advance(iter, i);
    return iter;
  };

  auto index = [&](auto iter){
    return iter - numbers.begin();
  };

  const int size = numbers.size();

  auto removals = [&](int i, int j) -> int{
    return i + size - j - 1;
  };


  int total_removals = size - 1;
  for(int i = 0; i < size; i++){
    const int searchingEle = k + at(i);
    auto searchIndex = index(std::upper_bound(itr(i), itr(size), searchingEle)) - 1;
    total_removals = min(removals(i, searchIndex), total_removals);
  }
  return total_removals;
}

// In this DP we store where we found the required ele
// and we start from there and go right
int removals_n(vector<int>& numbers, int k){
  sort(numbers.begin(), numbers.end());
  const auto size = numbers.size();
  auto at = const_accessor(numbers);
  vector<int> sol(size);
  auto dp = accessor(sol);

  dp(0) = 0;
  auto ans = size - 1;

  for(int i = 1; i < size; i++){
    dp(i) = i;
    int j = dp(i - 1);
    while(j != i && at(i) - at(j) > k){
      j++;
    }
    dp(i) = min(dp(i), j);
    ans = min(ans, size - (i - j + 1));
  }
  return ans;
}

int main(int argc, const char** argv) {
  vector<int> numbers = {1, 3, 4, 9, 10, 11, 12, 17, 20};
  std::cout<<removals_n(numbers, 4)<<std::endl;
    return 0;
}

