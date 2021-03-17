#include <bits/stdc++.h>
using namespace std;

#define f(i,k,n) for(int i = k; i < n; i++)
#define fo(i,k,n) for(i = k; i < n; i++)

template<typename T>
void print(T ele, string message = ""){
  cout<<message<<ele<<endl;
}

template<typename T>
void print(T begin, T end, string message = ""){
  cout<<message;
  while(begin != end){
    cout<<*begin<<" ";
    begin++;
  }
  cout << endl;
}

int equalPartitionUtilMySolution(int N, int* arr, int firstSum, int secondSum, int currentIndex){
  if(firstSum == secondSum) {
    return true;
  }
  if(currentIndex >= N){
    return false;
  }
  return equalPartitionUtilMySolution(N, arr, firstSum - arr[currentIndex], secondSum + arr[currentIndex], currentIndex + 1)
    || equalPartitionUtilMySolution(N, arr, firstSum, secondSum, currentIndex + 1);
}

int equalPartitionMySolution(int N, int arr[]) {
  int sum = 0;
  f(i, 0, N){
    sum += arr[i];
  }
  return equalPartitionUtilMySolution(N, arr, sum, 0, 0);
}

bool isTargetSumPresentMemoization(int* arr, int n, int targetSum, int currentIndex, vector<unordered_map<int, bool>> sumMap){
  if(targetSum == 0){
    return true;
  }
  if(currentIndex < 0){
    return false;
  }
  auto& internalMap = sumMap[currentIndex];
  if(internalMap.find(targetSum) != internalMap.end()){
    return internalMap[targetSum];
  }
  bool solution = isTargetSumPresentMemoization(arr, n, targetSum - arr[currentIndex],
      currentIndex - 1, sumMap)|| isTargetSumPresentMemoization(arr, n, targetSum,
        currentIndex - 1, sumMap);
  internalMap[targetSum] = solution;
  return solution;
}

bool isTargetSumPresent(int* arr, int n, int targetSum, vector<unordered_map<int, bool>> sumMap){
  f(i, 0, targetSum){
    sumMap[0][targetSum] = (arr[0] == targetSum) ? true : false;
  }
  f(i, 0, n){
    sumMap[i][0] = 1;
  }
  f(i, 1, n){
    f(j, 1, targetSum + 1){
      sumMap[i][j] = sumMap[i-1][j] || sumMap[i-1][j - arr[i]];
    }
  }
  return sumMap[n-1][targetSum];
}

int equalPartition(int N, int arr[]) {
  int sum = 0;
  f(i, 0, N){
    sum += arr[i];
  }
  if(sum % 2){
    return false;
  }
  vector<unordered_map<int, bool>> sumMap;
  f(i, 0, N){
    unordered_map<int, bool> vec;
    sumMap.push_back(vec);
  }
  return isTargetSumPresent(arr, N, sum/2, sumMap);
}

int main()
{
  int t;
  cin>>t;
  while(t --){
    int n;
    cin>>n;
    int arr[n];
    f(i, 0, n){
      cin>>arr[i];
    }
    cout<< equalPartition(n, arr)<<endl;
  }
}
