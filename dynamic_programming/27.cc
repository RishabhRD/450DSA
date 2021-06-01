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


int maxSubstring(const string& S){
  const int size = S.size();
  vector<int> vec;
  for(auto c : S){
    if(c == '1'){
      vec.push_back(-1);
    }else{
      vec.push_back(1);
    }
  }

  auto at = [&](int i){
    return vec.at(i);
  };

  vector<int> sums(size);

  auto sol = [&](int i) -> int&{
    return sums.at(i);
  };

  sol(0) = at(0);

  for(int i = 1; i < size; i++){
    sol(i) = max(sol(i - 1) + at(i), at(i));
  }


  return *max_element(sums.begin(), sums.end());
}

int main(int argc, const char** argv) {
  std::cout<<maxSubstring("11000010001")<<std::endl;
    return 0;
}
