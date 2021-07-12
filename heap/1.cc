
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

constexpr int parent(int i){
  return i % 2 ? i / 2 : i / 2 - 1;
}

constexpr int left(int i){
  return 2 * i + 1;
}

constexpr int right(int i){
  return 2 * i + 2;
}

void max_heapify(vector<int>& arr, int i, int heap_size){
  int l = left(i);
  int r = right(i);
  int largest = i;
  if(l < heap_size and arr[l] > arr[i]){
    largest = l;
  }
  if(r < heap_size and arr[r] > arr[largest]){
    largest = r;
  }

  if(i != largest){
    swap(arr[i], arr[largest]);
    max_heapify(arr, largest, heap_size);
  }
}

void make_heap(vector<int>& arr){
  const int size = arr.size();
  for(int i = size / 2 - 1; i >= 0; i--){
    max_heapify(arr, i, size);
  }
}

void heap_sort(vector<int>& arr){
  make_heap(arr);
  const int n = size(arr);
  int heap_size = n;
  for(int i = n; i > 0; i--){
    swap(arr[i], arr[0]);
    heap_size--;
    max_heapify(arr, 1, heap_size);
  }
}

int extract_max(vector<int>& arr){
  const int size = arr.size();
  if(size == 0){
    throw "Heap underflow";
  }
  const auto max = arr[0];
  swap(arr[0], arr[size - 1]);
  arr.pop_back();
  max_heapify(arr, 1, size - 1);
  return max;
}

int incr_key(vector<int>& arr, int i, int key){
  arr[i] = key;
  while(i > 0){
    swap(arr[i], arr[parent(i)]);
    i = parent(i);
  }
}

void insert(vector<int>& arr, int key){
  arr.push_back(INT32_MIN);
  incr_key(arr, size(arr) - 1, key);
}
