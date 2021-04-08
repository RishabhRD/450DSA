#include <vector>
#include <algorithm>
#include <iostream>


int maxProduct(std::vector<int>& nums) {
  const int size = nums.size();
  int min = nums[0];
  int max = nums[0];
  int maxProduct = nums[0];
  for(int i = 1; i < size; i++){
    int newMax = std::max(max * nums[i], std::max(nums[i], min * nums[i]));
    int newMin = std::min(max * nums[i], std::min(nums[i], min * nums[i]));
    if ( newMax > maxProduct ){
      maxProduct = newMax;
    }
    max = newMax;
    min = newMin;
  }
  return maxProduct;
}

int main() {
  std::vector<int> vec = {6, -3, -10, 0, 2};
  std::cout << maxProduct(vec) << std::endl;
}
