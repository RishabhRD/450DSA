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

int max_profit(const vector<int>& prices){
  auto price = accessor(prices);
  const auto size = prices.size();
  vector<int> profits(size);
  auto profit = accessor(profits);

  int max_price = price(size - 1);
  for(int i = size - 2; i >= 0; i--){
    max_price = max(max_price, price(i));
    profit(i) = max(profit(i + 1), max_price - price(i));
  }

  int min_price = price(0);
  for(int i = 1; i < size; i++){
    min_price = min(min_price, price(i));
    profit(i) = max(profit(i - 1), profit(i) + price(i) - min_price);
  }

  return profit(size - 1);
}

int max_profit_optmized(const vector<int>& prices){
  auto price = accessor(prices);
  const auto size = prices.size();
  if(size == 1){
    return 0;
  }
  int profit = 0;
  for(int i = 1; i < size; i++){
    if(price(i) > price(i - 1)){
      profit += (price(i) - price(i - 1));
    }
  }
  return profit;
}

int main(int argc, const char** argv) {
  cout << max_profit({1, 2, 3}) << endl;
    return 0;
}
