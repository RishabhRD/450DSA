#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

int lsi(const vector<int>& vec){
  const int size = vec.size();
  vector<int> sub(size);
  sub.at(0) = 1;
  for(int i = 1; i < size; i++){
    sub.at(i) = std::numeric_limits<int>::min();
    for(int j = 0; j < i; j++){
      int diff = std::abs(vec.at(i) - vec.at(j));
      if(diff == 1){
        if(sub.at(j) + 1 > sub.at(i)){
          sub.at(i) = sub.at(j) + 1;
        }
      }
    }
    if(sub.at(i) == std::numeric_limits<int>::min()){
      sub.at(i) = 1;
    }
  }
  return *std::max_element(sub.begin(), sub.end());
}

int longestSubsequence(int N, int A[])
{
  vector<int> vec;
  std::copy(A, A+N, std::back_inserter(vec));
  return lsi(vec);
}

int main(){
  std::cout<< lsi({10, 9, 4, 5, 4, 8, 6}) <<std::endl;
} 
