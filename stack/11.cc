#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <stack>
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

constexpr int get_ele(char c){
  return c - '0';
}

constexpr bool is_operator(char c){
  return c == '+' or c == '-' or c == '*' or c == '/';
}

int evaluatePostfix(string S) {
  stack<int> st;
  auto pop = [&]{
    const auto top = st.top();
    st.pop();
    return top;
  };
  auto operate = [&](auto c){
    const auto first_ele = pop();
    const auto second_ele = pop();
    if(c == '+'){
      st.push(first_ele + second_ele);
    }else if(c == '-'){
      st.push(second_ele - first_ele);
    }else if(c == '*'){
      st.push(first_ele * second_ele);
    }else{
      st.push(second_ele / first_ele);
    }
  };
  for(auto c : S){
    if(is_operator(c)){
      operate(c);
    }else{
      st.push(get_ele(c));
    }
  }
  return st.top();
}

int main(int argc, const char** argv) {
  cout << evaluatePostfix("231*+9-") << endl;
    return 0;
}
