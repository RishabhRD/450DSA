#include <unordered_set>
#include <queue>
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
requires(not(std::same_as<T, std::string> or std::same_as<T, std::string_view>)) std::ostream &
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

size_t difference(string_view s1, string_view s2) {
  size_t count = 0;
  const auto size = s1.size();
  for (size_t i = 0; i < size; i++) {
    if (s1[i] != s2[i])
      count++;
  }
  return count;
}

vector<string_view> neighbor(const string_view s1, const vector<string> &vec) {
  vector<string_view> neighbors;
  for (const auto &str : vec) {
    if (difference(s1, str) == 1)
      neighbors.emplace_back(str);
  }
  return neighbors;
}


class Solution {
public:
  int ladderLength(string beginWord, string endWord, const vector<string> &wordList) {
    if(beginWord == endWord) return 1;
    unordered_set<string_view> visited;
    auto contains = [&](string_view str){
      return visited.find(str) != end(visited);
    };
    queue<string_view> q;
    visited.insert(beginWord);
    q.push(beginWord);
    int cur_level = 1;
    while(not q.empty()){
      const auto size  = q.size();
      for(size_t i = 0; i < size; i++){
        auto top = q.front();
        q.pop();
        for(auto n : neighbor(top, wordList)){
          if(not contains(n)){
            if(n == endWord) return cur_level + 1;
            q.push(n);
            visited.insert(n);
          }
        }
      }
      cur_level++;
    }
    return 0;
  }
};

int main() {
  Solution sol;
  cout << sol.ladderLength("hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}) << endl;
    return 0;
}
