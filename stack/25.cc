#include <list>
#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <unordered_map>
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

class LRUCache {
private:
  unordered_map<int, list<pair<int, int>>::iterator> mp;
  list<pair<int, int>> lst;
  int cap;
  int size;
public:
  LRUCache(int cap) : cap(cap), size(0){}

  int get(int key) {
    if(mp.find(key) != mp.end()){
      const auto ans = mp[key]->second;
      lst.erase(mp[key]);
      lst.emplace_back(key, ans);
      mp.erase(key);
      mp[key] = prev(lst.end());
      return ans;
    }else{
      return -1;
    }
  }

  // Function for storing key-value pair.
  void set(int key, int value) {
    if(mp.find(key) != mp.end()){
      lst.erase(mp[key]);
      lst.emplace_back(key, value);
      mp[key] = prev(lst.end());
    }else{
      if(size < cap){
        lst.emplace_back(key, value);
        mp[key] = prev(lst.end());
        size++;
      }else{
        mp.erase(lst.front().first);
        lst.erase(begin(lst));
        lst.emplace_back(key, value);
        mp[key] = prev(lst.end());
      }
    }
  }
};
