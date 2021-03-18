#include <algorithm>
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

void combinationSumUtil(vector<int> &arr, int targetSum,
                        vector<vector<int>> &result, int currentIndex,
                        vector<int> &currentVector) {
  if (targetSum == 0) {
    result.push_back(currentVector);
    return;
  }
  if (targetSum < 0) {
    return;
  }
  while (currentIndex < arr.size() && targetSum - arr[currentIndex] >= 0) {
    currentVector.push_back(arr[currentIndex]);
    combinationSumUtil(arr, targetSum - arr[currentIndex], result, currentIndex,
                       currentVector);
    currentIndex++;
    currentVector.pop_back();
  }
}

vector<vector<int>> combinationSum(vector<int> &A, int B) {
  sort(A.begin(), A.end());
  int size = A.size();
  A.erase(unique(A.begin(), A.end()), A.end());
  vector<vector<int>> solution;
  vector<int> currentVector;
  combinationSumUtil(A, B, solution, 0, currentVector);
  return solution;
};

int main() {
  int n;
  cin >> n;
  vector<int> vec(n);
  f(i, 0, n) { cin >> vec[i]; }
  int targetSum;
  cin >> targetSum;
  auto sumVectors = combinationSum(vec, targetSum);
  for (auto &vec : sumVectors) {
    print(vec.begin(), vec.end());
  }
}
