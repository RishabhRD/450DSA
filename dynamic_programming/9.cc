#include <iostream>
#include <vector>

using namespace std;

// 1 2 3
// 1 2 3
// 1 2 3

template <typename T> concept is_container = requires(T a) {
  a.begin();
  a.end();
};

std::ostream &operator<<(std::ostream &os, const is_container auto &cont) {
  os << '{';
  for (const auto &x : cont) {
    os << x;
    os << " ";
  }
  os << '}';
  return os;
}

void printMatrix(const is_container auto &cont) {
  for (const auto &x : cont) {
    cout << x;
    cout << "\n";
  }
}

auto getMaximumMatrix(const vector<vector<int>> &vec) {
  const int size = vec.size();
  vector<vector<int>> maximumMatrix(size, vector<int>(size));
  auto maxAt = [&maximumMatrix](auto i, auto j) mutable -> int & {
    return maximumMatrix.at(i).at(j);
  };

  auto vecAt = [&vec](auto i, auto j) { return vec.at(i).at(j); };

  auto getMax = [&maximumMatrix, &maxAt, &size](auto i, auto j) {
    if (i - 1 >= 0) {
      if (i + 1 < size) {
        return std::max(maxAt(i + 1, j + 1), maxAt(i - 1, j + 1));
      } else {
        return maxAt(i - 1, j + 1);
      }
    } else {
      return maxAt(i + 1, j + 1);
    }
  };

  for (int i = 0; i < size; i++) {
    maxAt(i, size - 1) = vecAt(i, size - 1);
  }
  for (int i = size - 2; i >= 0; i--) {
    for (int j = 0; j < size; j++) {
      maxAt(j, i) = vecAt(j, i) + getMax(j, i);
    }
  }
  int max = maxAt(0, 0);
  for(int i = 1; i < size; i++){
    max = std::max(max, maxAt(i, 0));
  }
  return max;
}

int main() {
  vector<vector<int>> vec = {{1, 3, 3}, {2, 1, 4}, {0, 6, 4}};
  std::cout << getMaximumMatrix(vec) << std::endl;
};
