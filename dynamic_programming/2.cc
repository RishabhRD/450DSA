
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

static const int modulo = 1000000007;

int c(int n, int r){
  int C[n+1][r+1];
  f(i, 0, n+1){
    f(j, 0, n+ 1){
      if(j == 0 || j == i){
        C[i][j]  = 1;
      }else{
        C[i][j] = (C[i-1][j-1] + C[i-1][j]) % modulo;
      }
    }
  }
  return C[n][r];
}

int main()
{
  int t;
  cin>>t;
  while(t--){
    int n;
    cin>>n;
    int r;
    cin>>r;
    cout<<c(n, r)<<endl;
  }
}
