#include <queue>
#include <unordered_map>
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

string rearrangeString(string s){
  const int size = s.size();
  unordered_map<char, int> mp;
  for(auto c : s){
    mp[c]++;
    if(mp[c] > ((size + 1) / 2)){
      return "-1";
    }
  }
  priority_queue<pair<int, char>> pq;
  for(const auto& pr : mp){
    pq.push({pr.second, pr.first});
  }
  string str = "";
  while(not pq.empty()){
    auto first = pq.top();
    pq.pop();
    str += first.second;
    if(not pq.empty()){
      auto second = pq.top();
      pq.pop();
      str += second.second;
      second.first--;
      if(second.first > 0){
        pq.push(second);
      }
    }
    first.first--;
    if(first.first > 0){
      pq.push(first);
    }
  }
  return str;
}

int main(int argc, const char** argv) {
  cout << rearrangeString("kkk") << endl;
    return 0;
}
