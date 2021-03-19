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

int editDistance(string s1, string s2){
  int l1 = s1.length();
  int l2 = s2.length();
  int dp[l1+1][l2+1];
  for(int i = 0; i<=l1; i++){
    for(int j = 0; j<=l2; j++){
      if(i == 0){
        dp[i][j] = j;
      }else if(j == 0){
        dp[i][j] = i;
      }else{
        if(s1[i - 1] == s2[j - 1]){
          dp[i][j] = dp[i - 1][j - 1];
        }else{
          int insert = 1 + dp[i][j-1];
          int del = 1 + dp[i-1][j];
          int replace = 1 + dp[i-1][j-1];
          dp[i][j] = min(min(insert, del), replace);
        }
      }
    }
  }
  return dp[l1][l2];
}

int main()
{
  int t;
  cin>>t;
  while(t--){
  }
}
