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

int minJumps(const vector<int>& vec){
  const int size = vec.size();
  auto at = accessor(vec);
  vector<int> jumps(size , lmt<int>::max());
  auto sol = accessor(jumps);

  sol(size - 1) = 0;
  
  for(int i = size - 2; i >= 0; i--){
    for(int j = 0; j < at(i); j++){
      if(i + j + 1 >= size) break;
      if(sol(i + j + 1) < sol(i)){
        sol(i) = sol(i + j + 1) + 1;
      }
    }
  }

  if(sol(0) == lmt<int>::max()) sol(0) = -1;
  return sol(0);
}

int minJumpsOn(const vector<int>& vec){
  const int size = vec.size();
  auto at = accessor(vec);
  int maxReach = at(0); // maximum index we can reach
  int step = at(0); // number of steps we can still take
  int jump = 1; // number of jumps we have to make
  if(at(0) == 0){
    return -1;
  }
  for(int i = 1; i < size; i++){
    if(i == size - 1){
      return jump;
    }
    
    maxReach = max(maxReach , i + at(i));

    step--;

    if(step == 0){
      jump ++;
      if( i >= maxReach ){
        return -1;
      }
      step = maxReach - i;
    }
  }
}

int minJumps(int arr[], int n){
  vector<int> vec;
  std::copy(arr, arr + n, std::back_inserter(vec));
  return minJumpsOn(vec);
}

int main(){
  int n;
  cin>>n;
  vector<int> vec(n);
  for(int i = 0; i < n; i++){
    cin>>vec.at(i);
  }
  std::cout<<minJumps(vec)<<std::endl;
}
