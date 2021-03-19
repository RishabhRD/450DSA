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

ll exchangeUtil(int S[], int m, int requiredSum, int currentIndex, vector<vector<ll>> storage){
  if(requiredSum == 0){
    return 1;
  }
  if(requiredSum < 0){
    return 0;
  }
  if(currentIndex >= m){
    return 0;
  }
  if(storage[requiredSum][currentIndex] != -1){
    return storage[requiredSum][currentIndex];
  }
  ll answer =  exchangeUtil(S, m, requiredSum, currentIndex + 1, storage) + exchangeUtil(S, m, requiredSum - S[currentIndex], currentIndex, storage);
  storage[requiredSum][currentIndex] = answer;
  return answer;
}

ll exchange(int S[], int m, int requiredSum){
  vector<vector<ll>> storage;
  f(i, 0, requiredSum + 1){
    vector<ll> vec;
    f(j, 0, m){
      vec.push_back(-1);
    }
    storage.push_back(vec);
  }
  return exchangeUtil(S, m, requiredSum, 0, storage);
}

int main()
{
  int t;
  cin>>t;
  while(t--){
    int n;
    cin>>n;
    int m;
    cin>>m;
    int arr[m];
    f(i, 0, m){
      cin>>arr[i];
    }
    cout<<exchange(arr, m, n)<<endl;
  }
}
