#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int getPairsCount(int arr[], int n, int k) {
unordered_map<int, int> m;

        for (int i = 0; i < n; i++) 
            m[arr[i]]++;
        
        int twice_count = 0;
        for (int i = 0; i < n; i++) {
            twice_count += m[k - arr[i]];
            if (k - arr[i] == arr[i]) twice_count--;
        }

        return twice_count / 2;
}

int main(){
  int n;
  int k;
  std::cin>>n>>k;
  int arr[n];
  for(int i = 0;  i < k; i++){
    std::cin>>arr[i];
  }
  cout<<getPairsCount(arr, n, k)<<endl;
}
