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

int buyMaximumProducts(int n, int k, int price[]){
  vector<pair<int, int>> stocks;
  for(int i = 0; i < n; i++){
    stocks.emplace_back(price[i], i + 1);
  }
  sort(stocks.begin(), stocks.end(), [](const auto &a, const auto& b){
      return a.first < b.first;
      });
  int remaining_money = k;
  int stocks_bought = 0;
  for(int cur_index = 0; cur_index < stocks.size(); cur_index++){
    if(remaining_money < stocks[cur_index].first){
      break;
    }
    const int cur_price = stocks[cur_index].first;
    const int num_allowed = stocks[cur_index].second;
    const int max_buyable = remaining_money / cur_price;
    const int bought_item = min(max_buyable, num_allowed);
    remaining_money -= bought_item * cur_price;
    stocks_bought += bought_item;
  }
  return stocks_bought;
}
