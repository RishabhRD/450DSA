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

int knapSackUtil(int W, int * val, int* wt, int n, vector<vector<int>>& storage){
  if(n == 0){
    return 0;
  }
  if(W == 0){
    return 0;
  }
  if(storage[W][n-1] != -1){
    return storage[W][n-1];
  }
  
  if(wt[n - 1] > W){
    int answer = knapSackUtil(W, val, wt, n - 1, storage);
    storage[W][n-1] = answer;
    return answer;
  }

  int answer =  max(
      val[n-1] + knapSackUtil(W - wt[n - 1], val, wt, n - 1, storage),
      knapSackUtil(W, val, wt, n - 1, storage)
      );
  storage[W][n-1] = answer;
  return answer;
}

int knapSack(int W, int wt[], int val[], int n) {
  vector<vector<int>> storage;
  f(i, 0, W+1){
    vector<int> vec;
    f(j, 0, n){
      vec.push_back(-1);
    }
    storage.push_back(vec);
  }
  return knapSackUtil(W, val, wt, n, storage);
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin>>n;
    int w;
    cin>>w;
    int values[n];
    int weight[n];
    f(i, 0, n){
      cin>>values[i];
    }
    f(i, 0, n){
      cin>>weight[i];
    }
    cout<<knapSack(w, weight, values, n)<<endl;
  }
}
