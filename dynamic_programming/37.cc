#include <iostream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>
#include <array>
#include <concepts>

using namespace std;

template <typename T> concept is_container = requires(T&& a) {
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

int wordBreak(const string& A, vector<string> &B) {
  auto contains = [&](int i, int j){
    const auto str = A.substr(i, j - i + 1);
    return std::find(B.begin(), B.end(), str) != B.end();
  };

  auto at = accessor(A);

  const int size = A.size();

  vector<bool> dp(size);
  auto sol = accessor(dp);

  for(int i = 0; i < size; i++){
    if(sol(i) == false && contains(0, i)){
      sol(i) = true;
    }
    
    if(sol(i) == true){
      if(i == size - 1){
        return true;
      }

      for(int j = i + 1; j < size; j++){
        if(sol(j) == false && contains(i + 1, j)){
          sol(j) = true;
        }
        if(j == size - 1 && sol(j) == true){
          return true;
        }
      }
    }
  }

  return false;
}

int main(int argc, const char** argv) {
    return 0;
}
