#include <vector>
vector<int> valueEqualToIndex(int arr[], int n) {
  vector<int> vec;
  for(int i = 0; i < n; i++){
    if(arr[i] == i)
      vec.push_back(i);
  }
  return vec;
}
