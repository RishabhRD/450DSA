#include <bits/stdc++.h>
using namespace std;

#define f(i, k, n) for (int i = k; i < n; i++)
#define fo(i, k, n) for (i = k; i < n; i++)

template <typename T> void print(T ele, string message = "") {
  cout << message << ele << endl;
}

template <typename T> void print(T begin, T end, string message = "") {
  cout << message;
  while (begin != end) {
    cout << *begin << " ";
    begin++;
  }
  cout << endl;
}

template <typename T> T toNumber(const string &s) {
  T answer = 0;
  int size = s.length();
  for (int i = 0; i < size; i++) {
    T num = s[i] - '0';
    answer = (answer * 10) + num;
  }
  return answer;
}

using ll = long long;
#define toInt toNumber<int>
#define toLL toNumber<ll>
#define toLong toLong<long>

bool isKPartitionPossibleUtil(int *arr, int n, int *subsetSumArray, bool *taken,
                              int requiredSum, int k, int currentSubsetIndex,
                              int currentArrayIndex) {
  if (requiredSum == subsetSumArray[currentSubsetIndex]) {
    if (currentSubsetIndex == k - 2) {
      return true;
    }
    return isKPartitionPossibleUtil(arr, n, subsetSumArray, taken, requiredSum,
                                    k, currentSubsetIndex + 1, n - 1);
  }

  for(int i = currentArrayIndex; i >= 0; i--) {
    if (taken[i]) {
      continue;
    }
    int tmp = subsetSumArray[currentSubsetIndex] + arr[i];
    if (tmp <= requiredSum) {
      taken[i] = true;
      subsetSumArray[currentSubsetIndex] += arr[i];
      bool answer =
          isKPartitionPossibleUtil(arr, n, subsetSumArray, taken, requiredSum,
                                   k, currentSubsetIndex, i - 1);
      taken[i] = false;
      subsetSumArray[currentArrayIndex] -= arr[i];
      if (answer) {
        return true;
      }
    }
  }
  return false;
}

bool isKPartitionPossible(int *arr, int n, int k) {
  if (k == 1) {
    return true;
  }
  if (n < k) {
    return false;
  }
  int totalSum = 0;
  f(i, 0, n) { totalSum += arr[i]; }
  if (totalSum % k) {
    return false;
  }
  int requiredSum = totalSum / k;
  bool taken[n];
  f(i, 0, n) { taken[i] = false; }
  int subsetSumArray[n];
  f(i, 0, n) { subsetSumArray[i] = 0; }
  subsetSumArray[0] = arr[n - 1];
  taken[n - 1] = true;
  return isKPartitionPossibleUtil(arr, n, subsetSumArray, taken, requiredSum, k,
                                 0, n - 1);
}

int main() {
  int arr[] = {2, 1, 4, 5, 3, 3};
  int N = sizeof(arr) / sizeof(arr[0]);
  int K = 3;

  if (isKPartitionPossible(arr, N, K))
    cout << "Partitions into equal sum is possible.\n";
  else
    cout << "Partitions into equal sum is not possible.\n";
}
