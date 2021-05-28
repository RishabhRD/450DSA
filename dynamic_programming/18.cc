#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int msi(const std::vector<int>& vec){
  vector<int> sums(vec.size());
  sums.at(0) = vec.at(0);

  const int size = vec.size();

  for(int i = 1; i < size; i++){
    sums.at(i) = std::numeric_limits<int>::min();
    for(int j = 0; j < i; j++){
      if(vec.at(i) > vec.at(j)){
        if(sums.at(j) + vec.at(i) > sums.at(i)){
          sums.at(i) = sums.at(j) + vec.at(i);
        }
      }
    }
    if(sums.at(i) == std::numeric_limits<int>::min()){
      sums.at(i) = vec.at(i);
    }
  }
  return *std::max_element(sums.begin(), sums.end());
}

int maxSumIS(int arr[], int n) {
  vector<int> vec;
  std::copy(arr, arr + n, std::back_inserter(vec));
  return msi(vec);
}

int main(){
  std::cout<< msi({44,42,38,21,15,22,13,27}) << std::endl;
}
