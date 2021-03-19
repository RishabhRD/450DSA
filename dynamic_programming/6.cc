
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

int countFriendsPairing(int n){
  int dp[n+1];
  for(int i = 0; i <= n ; i++){
    if(i == 0){
      dp[i] = 0;
    }else if(i == 1 ){
      dp[i] = 1;
    }else{
      dp[i] = dp[i-1] + (i-1) * dp[i-2];
    }
  }
  return dp[n];
}

int main()
{
  int t;
  cin>>t;
  while(t--){
  }
}
