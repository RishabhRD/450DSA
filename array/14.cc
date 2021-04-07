#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void nextPermutationUsingStl(vector<int>& nums) {
  std::next_permutation(nums.begin(), nums.end());
}

void nextPermutation(vector<int>& nums) {
  if(nums.size() == 0){
    return;
  }
  auto last = nums.end();
  last--;
  if(nums.begin() == last){
    return;
  }
  auto breakingItr = nums.end();
  for(auto itr  = last - 1; itr >= nums.begin(); itr --){
    if(*itr < *(itr + 1)){
      breakingItr = itr;
      break;
    }
  }
  /* cout<<"Breaking: "<<*breakingItr<<endl; */
  if(breakingItr == nums.end()){
    std::reverse(nums.begin(), nums.end());
    return;
  }
  auto greaterItr = nums.end();
  for(auto itr = last; itr > breakingItr; itr--){
    if(*itr > *breakingItr){
      greaterItr = itr;
      break;
    }
  }
  /* cout<<"Greater: "<<*greaterItr<<endl; */
  std::iter_swap(breakingItr, greaterItr);
  std::reverse(breakingItr + 1, nums.end());
}

void print(vector<int>& vec){
  for(int x : vec){
    cout<<x<<" ";
  }
  cout<<endl;
}

int main()
{
  std::vector<int> vec{1,2,3};
  nextPermutation(vec);
  print(vec);
  nextPermutation(vec);
  print(vec);
  nextPermutation(vec);
  print(vec);
  nextPermutation(vec);
  print(vec);
  nextPermutation(vec);
  print(vec);
  nextPermutation(vec);
  print(vec);
  nextPermutation(vec);
  print(vec);
  nextPermutation(vec);
  print(vec);
}
