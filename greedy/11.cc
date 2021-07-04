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

template <typename T, std::size_t N>
constexpr std::size_t array_size(const T (&)[N]) noexcept{
  return N;
}


int minimumCostOfBreaking(vector<int>& x[], vector<int>& y[]){
  sort(cbegin(x), cend(x), greater<int>{});
  sort(cbegin(y), cend(y), greater<int>{});
  const auto x_size = x.size();
  const auto y_size = y.size();
  auto num_horizontal = 1;
  auto num_vertical = 1;
  decltype(x_size) i = 0;
  decltype(y_size) j = 0;
  auto total_cost = 0;
  while(i < x_size && j < y_size){
    if(x[i] <= y[j]){
      total_cost += (x[i] * num_horizontal);
      num_vertical++;
      i++;
    }else{
      total_cost += (y[j] * num_vertical);
      num_horizontal++;
      j++;
    }
  }
  if(i < x_size){
    total_cost += (x[i] * num_horizontal);
  }
  if(j < y_size){
    total_cost += (y[j] * num_vertical);
  }
  return total_cost;
}
