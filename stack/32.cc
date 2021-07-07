#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <queue>
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

vector<long long> printFirstNegativeInteger(long long int A[], long long int N,
                                            long long int K) {
  queue<pair<long long, long long>> q;
  for(int i = 0; i < N; i++){
    if(A[i] < 0){
      q.push({i, A[i]});
    }
  }
  vector<long long> vec;
  for(int i = 0; i < N - K + 1; i++){
    if(q.empty()){
      vec.push_back(0);
    }else{
      if(q.front().first <= i + K - 1){
        vec.push_back(q.front().second);
      }else{
        vec.push_back(0);
      }
      if(i == q.front().first){
        q.pop();
      }
    }
  }
  return vec;
}

int main(int argc, const char** argv) {
  long long arr[] = {-8, 2, 3, -6, 10};
  auto vec = printFirstNegativeInteger(arr, size(arr), 2);
  cout << vec << endl;
    return 0;
}
