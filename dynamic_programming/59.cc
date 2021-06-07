#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>

using namespace std;

template <typename T> concept is_container = requires(T a) {
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

struct Pair{
  int start;
  int end;
  bool operator<(const Pair& p){
    return this->end < p.start;
  }
};

/* ostream& operator<<(ostream& os, const Pair& p){ */
/*   os << '(' << p.start << ", " << p.end << ")"; */
/*   return os; */
/* } */

bool operator<(const Pair& p1, const Pair& p2){
  return p1.end < p2.start;
}

int flc(vector<Pair>& pairs){
  sort(pairs.begin(), pairs.end(), [](const Pair& p1, const Pair& p2){
      return p1.start < p2.start;
      });
  const auto at = const_accessor(pairs);
  const auto size = pairs.size();
  vector<int> dp(size, 1);
  const auto sol = accessor(dp);
  for(int i = 1; i < size; i++){
    for(int j = 0; j < i; j++){
      if(at(j) < at(i)){
        sol(i) = max(1 + sol(j), sol(i));
      }
    }
  }
  return sol(size - 1);
}

Pair createPair(const vector<int>& ele){
  return {ele.at(0), ele.at(1)};
}

vector<Pair> createPairVector(const vector<vector<int>>& vec){
  vector<Pair> ans;
  for(const auto& ele : vec){
    ans.push_back(createPair(ele));
  }
  return ans;
}

int findLongestChain(vector<vector<int>> &pairs) {
  vector<Pair> vec = createPairVector(pairs);
  return flc(vec);
}

int main(int argc, const char** argv) {
  vector<Pair> vec = {
{-10,-8},{8,9},{-5,0},{6,10},{-6,-4},{1,7},{9,10},{-4,7}
  };
  cout << flc(vec) << endl;
    return 0;
}
