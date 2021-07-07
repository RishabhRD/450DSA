#include <deque>
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

int sum_of_max_min(const vector<int>& arr, int k){
  const int size = arr.size();
  deque<int> incr, decr;
  auto push = [&](int i){
    while((not incr.empty()) and arr[incr.back()] >= arr[i]){
      incr.pop_back();
    }
    while((not decr.empty()) and arr[decr.back()] <= arr[i]){
      decr.pop_back();
    }
    incr.push_back(i);
    decr.push_back(i);
  };
  for(int i = 0; i < k; i++){
    push(i);
  }
  int sum = 0;
  for(int i = 0; i < size - k + 1; i++){
    sum += arr[incr.front()];
    sum += arr[decr.front()];
    if(incr.front() == i){
      incr.pop_front();
    }
    if(decr.front() == i){
      decr.pop_front();
    }
    push(i + k);
  }
  return sum;
}

int main(int argc, const char** argv) {
  cout << sum_of_max_min({2, 5, -1, 7, -3, -1, -2}  , 3) << endl;
    return 0;
}
