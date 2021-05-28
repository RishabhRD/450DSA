#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int ms3(const vector<int> &vec) {
  int size = vec.size();
  vector<int> sums(size);

  sums.at(0) = vec.at(0);
  sums.at(1) = vec.at(1) + vec.at(0);
  sums.at(2) =
      std::max({sums.at(1), vec.at(0) + vec.at(2), vec.at(1) + vec.at(2)});

  for(int i = 3; i < size; i++){
    sums.at(i) = std::max({
        sums.at(i - 1),
        sums.at(i - 2) + vec.at(i),
        sums.at(i - 3) + vec.at(i - 1) + vec.at(i)
        });
  }
  return sums.back();
}

int main(){
  std::cout<<ms3({1, 2, 3})<<std::endl;
}
