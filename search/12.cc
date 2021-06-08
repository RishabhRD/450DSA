#include <iostream>
#include <algorithm>
using namespace std;
long long countTriplets(long long arr[], int n, long long sum) {
  if(n <= 2){
    return 0;
  }
  sort(arr, arr + n);
  long long count = 0;
  for(int i = 0; i < n; i++){
    long long targetSum = sum - arr[i];
    int low = i + 1;
    int high = n - 1;
    while(low < high){
      if(arr[low] + arr[high] >= targetSum){
        high--;
      }else{
        // why? because all elements sum from low to high would be less than k
        // because of sorting. And we don't include low itself.
        count += high - low;
        low++;
      }
    }
  }
  return count;
}

int main(int argc, const char** argv) {
  long long arr[] = {-2, 0, 1, 3};
  int size = sizeof(arr) / sizeof(long long);
  cout << countTriplets(arr, size, 2) << endl;
    return 0;
}
