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

int maxSquare(int n, int m, const vector<vector<int>>& mat) {
  auto at = [&](int i, int j) {
    return mat.at(i).at(j);
  };
  vector<vector<int>> squares(n, vector<int>(m));

  auto sol = [&](int i, int j) -> int& {
    return squares.at(i).at(j);
  };

  for(int i = 0; i < n; i++){
    sol(i, 0) = at(i, 0);
  }

  for(int i = 0; i < m; i++){
    sol(0, i) = at(0, i);
  }

  for(int i = 1; i < n; i++){
    for(int j = 1; j < m ; j++){
      if(at(i, j) != 1){
        sol(i, j) = 0;
      }else{
        sol(i, j) = 1 + std::min({sol(i, j - 1), sol(i - 1, j), sol(i - 1, j - 1)});
      }
    }
  }

  int ans = 0;
  for(auto& vec : squares){
    int val = *std::max_element(vec.begin(), vec.end());
    if(val > ans) ans = val;
  }

  return ans;
}

int main(){
  vector<vector<int>> vec = {
    {0, 1, 1, 0, 1},
    {1, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0}
  };
  std::cout<<maxSquare(vec.size(), vec.at(0).size(), vec) << std::endl;
}
