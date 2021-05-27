#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int ls(const std::vector<int> &vec) {
  const int size = vec.size();
  std::vector<int> ans(size);
  ans[0] = 1;
  for(int i = 1; i < size; i++){
    ans[i] = std::numeric_limits<int>::min();
    for(int j = 0; j < i; j++){
      if(vec[i] > vec[j]){
        if(1 + ans[j] > ans[i]){
          ans[i] = 1 + ans[j];
        }
      }
    }
    if(ans[i] == std::numeric_limits<int>::min()){
      ans[i] = 1;
    }
  }
  return *std::max_element(ans.begin(), ans.end());
}

int lis(const std::vector<int>& vec){
  std::vector<int> subseq;
  subseq.push_back(vec.front());
  for(auto itr = vec.begin() + 1; itr != vec.end(); itr++){
    if(*itr > subseq.back()){
      subseq.push_back(*itr);
    }else{
      auto eleItr = std::upper_bound(subseq.begin(), subseq.end(), *itr);
      *eleItr = *itr;
    }
  }
  return subseq.size();
}

int longestSubsequence(int n, int a[]) {
  std::vector<int> vec;
  std::copy(a, a + n, std::back_inserter(vec));
  return ls(vec);
}

int main(){
  std::cout<<lis({5, 8, 3, 7, 9, 1})<<std::endl;
}
