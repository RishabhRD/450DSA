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

int eggDrop(const int numEggs, const int numFloors) {
  vector<vector<int>> attempts(numEggs + 1, vector<int>(numFloors + 1));
  auto at = [&](int i, int j) -> int&{
    return attempts.at(i).at(j);
  };

  for(int i = 0; i <= numFloors; i++){
    at(1, i) = i;
  }

  for(int i = 0; i <= numEggs; i++){
    at(i, 1) = 1;
    at(i, 0) = 0;
  }

  for(int i = 2; i <= numEggs; i++){
    for(int j = 2; j <= numFloors; j++){
      at(i, j) = numeric_limits<int>::max();
      for(int k = 1; k <= j; k++){
        auto currentFloorAttempts = 1 + max(at(i - 1, k - 1), at(i, j - k));
        if(at(i, j) > currentFloorAttempts){
          at(i, j) = currentFloorAttempts;
        }
      }
    }
  }
  return at(numEggs, numFloors);
}

int main(){
  std::cout<<eggDrop(2, 10)<<std::endl;
}
