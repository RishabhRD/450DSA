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

int maxSum(int stack1[], int stack2[], int stack3[], int n1, int n2, int n3) {
  auto first_sum = accumulate(stack1, stack1 + n1, 0);
  auto second_sum = accumulate(stack2, stack2 + n2, 0);
  auto third_sum = accumulate(stack3, stack3 + n3, 0);
  if(first_sum == second_sum and second_sum == third_sum) return first_sum;
  auto first_index = 0;
  auto second_index = 0;
  auto third_index = 0;
  while(first_sum > 0 or second_sum > 0 or third_sum > 0){
    auto max_sum = max({first_sum, second_sum, third_sum});
    if(max_sum == first_sum){
      first_sum = first_sum - stack1[first_index];
      first_index++;
    }else if(max_sum == second_sum){
      second_sum = second_sum - stack2[second_index];
      second_index++;
    }else{
      third_sum = third_sum - stack2[third_index];
      third_index++;
    }
    if(first_sum == second_sum and second_sum == third_sum) return first_sum;
  }
  return 0;
}
