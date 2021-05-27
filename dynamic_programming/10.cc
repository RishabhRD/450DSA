#include <array>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

template <typename T, std::size_t... Is>
constexpr std::array<T, sizeof...(Is)>
create_array(T value, std::index_sequence<Is...>) {
  // cast Is to void to remove the warning: unused value
  return {{(static_cast<void>(Is), value)...}};
}

auto infMin(int currentStationTiming, int otherStationTiming, int processingTime){
  if(processingTime == std::numeric_limits<int>::max()){
    return currentStationTiming;
  }
  return std::min(currentStationTiming, otherStationTiming + processingTime);
}

int carAssembly(const std::array<vector<int>, 2> &A,
                const std::array<vector<int>, 2> &T, int e1, int e2, int x1,
                int x2) {
  const int size = A[0].size() + 2;
  array<vector<int>, 2> a;
  array<vector<int>, 2> t;
  a[0].push_back(e1);
  a[1].push_back(e2);
  a[0].insert(std::end(a[0]), std::begin(A[0]), std::end(A[0]));
  a[1].insert(std::end(a[1]), std::begin(A[1]), std::end(A[1]));
  a[0].push_back(x1);
  a[1].push_back(x2);

  t[0].push_back(std::numeric_limits<int>::max());
  t[1].push_back(std::numeric_limits<int>::max());
  t[0].insert(std::end(t[0]), std::begin(T[0]), std::end(T[0]));
  t[1].insert(std::end(t[1]), std::begin(T[1]), std::end(T[1]));
  t[0].push_back(std::numeric_limits<int>::max());
  t[1].push_back(std::numeric_limits<int>::max());

  auto timing =
      create_array(std::vector<int>(size), std::make_index_sequence<2>());
  timing[0][0] = a[0][0];
  timing[1][0] = a[1][0];
  for (int i = 1; i < size; i++) {
    timing[0][i] =
        a[0][i] + infMin(timing[0][i - 1], timing[1][i - 1], t[1][i - 1]);
    timing[1][i] =
        a[1][i] + infMin(timing[1][i-1], timing[0][i-1], t[0][i - 1]);
  }
  return std::min(timing[0].back(), timing[1].back());
}

int main(int argc, const char **argv) {
  array<vector<int>, 2> a = {std::vector<int>{4, 5, 3, 2},
                             std::vector<int>{2, 10, 1, 4}};

  array<vector<int>, 2> t = {std::vector<int>{7, 4, 5},
                             std::vector<int>{9, 2, 8}};

  int e1 = 10;
  int e2 = 12;
  int x1 = 18;
  int x2 = 7;
  cout << carAssembly(a, t, e1, e2, x1, x2) <<endl;
  return 0;
}
