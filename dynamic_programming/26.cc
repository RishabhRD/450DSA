#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

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

int maximumPath(int N, const vector<vector<int>>& matrix) {
  int size = matrix.size();
  auto at = [&](int i, int j){
    return matrix.at(i).at(j);
  };
  vector<vector<int>> sums(size, vector<int>(size));
  auto sol = [&](int i, int j) -> int&{
    return sums.at(i).at(j);
  };

  auto csol = [&](int i, int j) -> int{
    if(j < 0 || j >= size){
      return 0;
    }
    return sums.at(i).at(j);
  };

  for(int i = 0; i < size; i++){
    sol(size - 1, i) = at(size - 1, i);
  }

  for(int i = size - 2; i >= 0; i--){
    for(int j = 0; j < size; j++){
      sol(i, j) = at(i, j) + max({
          csol(i + 1, j - 1),
          csol(i + 1, j),
          csol(i + 1, j +1)
          });
    }
  }
  int max = 0;
  for(int i = 0; i < size; i++){
    if(max < csol(0, i)){
      max = csol(0, i);
    }
  }
  return max;
}

int main(){
  vector<vector<int>> vec = {
    {348, 391},
    {618, 193}
  };
  std::cout<<maximumPath(vec.size(), vec)<<std::endl;
}
