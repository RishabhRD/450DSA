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

template <typename T>
int find_peak(const T& at, int low, int high){
  while(high >= low){
    if(high == low){
      return low;
    }
    int mid = (low + high) / 2;
    if(mid < high && at(mid) > at(mid + 1)){
      return mid;
    }
    if(mid > low && at(mid) < at(mid - 1)){
      return mid - 1;
    }

    if(at(low) >= at(mid)){
      high = mid - 1;
    }else{
      low = mid + 1;
    }
  }
  return -1;
}

template <typename T>
int bsearch(const T& at, int low, int high, int ele){
  while(high >= low){
    int mid = (low + high) / 2;
    if(at(mid) == ele){
      return mid;
    }
    if(at(mid) < ele){
      low = mid + 1;
    }else{
      high = mid - 1;
    }
  }
  return -1;
}

int search(const vector<int>& nums, int target) {
  auto at = accessor(nums);
  const auto size = nums.size();
  auto peak = find_peak(at, 0, size - 1);
  if(peak == -1){
    return bsearch(at, 0, size - 1, target);
  }else{
    int firstSearch = bsearch(at, 0, peak, target);
    if(firstSearch != -1){
      return firstSearch;
    }
    int secondSearch = bsearch(at, peak + 1, size - 1, target);
    return secondSearch;
  }
}
int search(int* arr, int l, int h, int key){
  auto at = [&](int i){
    return arr[i];
  };
  auto peak = find_peak(at, l, h);
  if(peak == -1){
    return bsearch(at, 0, h, key);
  }else{
    int firstSearch = bsearch(at, 0, peak, key);
    if(firstSearch != -1){
      return firstSearch;
    }
    int secondSearch = bsearch(at, peak + 1, h, key);
    return secondSearch;
  }
}

int main(int argc, const char** argv) {
  cout << search({1, 3}, 0) << endl;
    return 0;
}
