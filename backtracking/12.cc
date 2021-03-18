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

void findMaximumNumUtil(int currentIndex, int k, string &str,
                          string &maxNum) {
  /* cout<<str<< " "<<k<<" "<<currentIndex<<endl; */
  if(str.compare(maxNum) > 0){
    string temp = str;
    maxNum = str;
  }
  if(currentIndex >= str.length() || k <= 0){
    return;
  }
  int size = str.length();
  char maxChar = str[currentIndex];
  f(i, currentIndex + 1, size){
    if(maxChar < str[i]){
      maxChar = str[i];
    }
  }
  if(maxChar != str[currentIndex]){
    k--;
  }
  f(i, currentIndex, size) {
    if(str[i] == maxChar){
    swap(str[currentIndex], str[i]);
    findMaximumNumUtil(currentIndex + 1, k , str, maxNum);
    swap(str[currentIndex], str[i]);
    }
  }
}

string findMaximumNum(string str, int k) {
  string max = str;
  findMaximumNumUtil(0, k, str, max);
  return max;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    string str;
    cin >> str;
    int k;
    cin >> k;
    cout << findMaximumNum(str, k) << endl;
  }
}
