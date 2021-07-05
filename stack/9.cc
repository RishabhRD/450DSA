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

int celebrity(vector<vector<int>> &M, int n) {
  auto knows = [&](int a, int b){
    return M[a][b];
  };
  stack<int> st;
  for(int i = 0; i < n; i++){
    st.push(i);
  }
  while(st.size() > 1){
    int first = st.top();
    st.pop();
    int second = st.top();
    st.pop();
    if(knows(first, second)){
      st.push(second);
    }else{
      st.push(first);
    }
  }
  const int candidate = st.top();
  for(int i = 0; i < n; i++){
    if((i != candidate) and (knows(candidate, i) or not knows(i, candidate))){
      return -1;
    }
  }
  return candidate;
}

int main(int argc, const char** argv) {
  vector<vector<int>> vec = {
    {0 1 0},
    {0 0 0}, 
    {0 1 0}
  };
  cout << celebrity(vec, 3) << endl;
    return 0;
}
