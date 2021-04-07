#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

// Best solution is O(n) with O(1) extra space without mutating the array.
// Hint: consider array as linked list

int findDuplicateWithAdditional(vector<int> &nums) {
  vector<int> markerStorage(nums.size());
  auto isDuplicate = [&markerStorage](int num) {
    markerStorage[num]++;
    return markerStorage[num] > 1;
  };
  auto answer = std::find_if(nums.begin(), nums.end(), isDuplicate);
  return *answer;
}

int findDuplicateWithMutating(vector<int> &nums) {
  auto isDuplicate = [&nums](int num) {
    if (num < 0) {
      num = 0 - num;
    }
    if (nums[num] < 0) {
      return true;
    } else {
      nums[num] = 0 - nums[num];
    }
    return false;
  };
  auto answer = *(std::find_if(nums.begin(), nums.end(), isDuplicate));
  return std::abs(answer);
}

int findDuplicate(vector<int> &nums) {
  int slowIndex = nums[0];
  int fastIndex = nums[nums[0]];
  while(slowIndex != fastIndex){
    slowIndex = nums[slowIndex];
    fastIndex = nums[nums[fastIndex]];
  }
  slowIndex = 0;
  while(nums[fastIndex] != nums[slowIndex]){
    slowIndex = nums[slowIndex];
    fastIndex = nums[fastIndex];
  }
  return nums[slowIndex];
}

int main() {
  vector<int> vec = {1, 3, 4, 2, 2};
  cout << findDuplicate(vec) << endl;
}
