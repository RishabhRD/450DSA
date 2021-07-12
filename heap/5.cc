#include <queue>
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

struct Triplet{
  int val;
  int x;
  int y;
};

bool operator<(const Triplet& t1, const Triplet& t2) noexcept{
  return t1.val > t2.val;
}

vector<int> mergeKArrays(vector<vector<int>> arr, int K) {
  vector<int> dest;
  priority_queue<Triplet> pq;
  for(int i = 0; i < K; i++){
    pq.push({arr[i][0], i, 0});
  }
  while(not pq.empty()){
    auto top = pq.top();
    pq.pop();
    dest.push_back(top.val);
    if(top.y + 1 < K){
      pq.push({arr[top.x][top.y + 1], top.x, top.y + 1});
    }
  }
  return dest;
}

int main(int argc, const char** argv) {
  vector<vector<int>> arr = {
    {57, 81}, {63, 71}
  };
  cout << mergeKArrays(arr, 2) << endl;
    return 0;
}
